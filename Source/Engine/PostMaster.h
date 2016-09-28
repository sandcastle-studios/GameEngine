#pragma once

template<typename TMessageType>
class Subscriber;

enum class ReceiveResult
{
	eContinue,
	eStop
};

template <typename TMessageType>
struct SubscriptionContainer
{
	Subscriber<TMessageType> * subscriber;
	int priority;
	bool isRemoved;
};

template <typename TMessageType>
class MessageCollection
{
public:
	static void AddSubscriber(Subscriber<TMessageType> & aSubscriber, int aPriority);
	static void RemoveSubscriber(const Subscriber<TMessageType> & aSubscriber);

	static void Distribute(const TMessageType & aMessageType);

private:
	static std::vector<SubscriptionContainer<TMessageType>> ourSubscribers;
	static size_t ourEnumerationCounter;
};

template <typename TMessageType>
std::vector<SubscriptionContainer<TMessageType>> MessageCollection<TMessageType>::ourSubscribers;

template <typename TMessageType>
size_t MessageCollection<TMessageType>::ourEnumerationCounter = 0;

template <typename TMessageType>
void MessageCollection<TMessageType>::AddSubscriber(Subscriber<TMessageType> & aSubscriber, int aPriority)
{
	SubscriptionContainer<TMessageType> container;
	container.isRemoved = false;
	container.priority = aPriority;
	container.subscriber = &aSubscriber;

	// Insert subscriber before first element that has the same or greater priority than it resulting in it being called last
	auto it = std::lower_bound(ourSubscribers.begin(), ourSubscribers.end(), container, [](const SubscriptionContainer<TMessageType> & aLeft, const SubscriptionContainer<TMessageType> & aRight) -> bool
	{
		return aLeft.priority < aRight.priority;
	});

	ourSubscribers.insert(it, container);
}

template <typename TMessageType>
void MessageCollection<TMessageType>::RemoveSubscriber(const Subscriber<TMessageType>& aSubscriber)
{
	// Find first element with the same priority as the one to remove
	SubscriptionContainer<TMessageType> referenceContainer;
	referenceContainer.priority = aSubscriber.GetPriority();

	auto it = std::lower_bound(ourSubscribers.begin(), ourSubscribers.end(), referenceContainer, [] (const SubscriptionContainer<TMessageType> & aLeft, const SubscriptionContainer<TMessageType> & aRight) -> bool
	{
		return aLeft.priority < aRight.priority;
	});
	
	while (true)
	{
		if (it == ourSubscribers.end())
		{
			Error("Tried to remove a subscriber that could not be found.");
		}

		if (it->priority != aSubscriber.GetPriority())
		{
			Error("Tried to remove a subscriber that could not be found.");
		}

		if (it->subscriber == &aSubscriber)
		{
			// Mark us as removed for later removal
			it->isRemoved = true;
			break;
		}
		
		++it;
	}
}

template <typename TMessageType>
void MessageCollection<TMessageType>::Distribute(const TMessageType& aMessageType)
{
	ourEnumerationCounter++;

	for (int i=static_cast<int>(ourSubscribers.size()) - 1; i >= 0; i--)
	{
		if (ourSubscribers[i].isRemoved == true)
		{
			// We can only safely remove components when we know we're the only function iterating
			if (ourEnumerationCounter == 1)
			{
				ourSubscribers.erase(ourSubscribers.begin() + i);
			}
			continue;
		}

		ReceiveResult result = ourSubscribers[i].subscriber->Receive(aMessageType);

		if (result == ReceiveResult::eStop)
		{
			break;
		}
	}

	ourEnumerationCounter--;
}

template<typename TMessageType = void>
class Subscriber
{
public:
	virtual ~Subscriber();

	int GetPriority() const;

	virtual ReceiveResult Receive(const TMessageType & aMessage) = 0;

protected:
	Subscriber(int aPriority = 0);

private:
	int myPriority;
};

template <typename TMessageType>
Subscriber<TMessageType>::Subscriber(int aPriority)
{
	myPriority = aPriority;
	MessageCollection<TMessageType>::AddSubscriber(*this, aPriority);
}

template <typename TMessageType>
Subscriber<TMessageType>::~Subscriber()
{
	MessageCollection<TMessageType>::RemoveSubscriber(*this);
}

template <typename TMessageType>
int Subscriber<TMessageType>::GetPriority() const
{
	return myPriority;
}

template <typename TMessageType>
class Subscription : public Subscriber<TMessageType>
{
public:
	template<typename TReceiveFunction, typename = std::enable_if<std::is_same<ReceiveResult, std::result_of<TReceiveFunction>>::value>::type>
	Subscription(const TReceiveFunction & aReceiveFunction, int aPriority = 0)
		: Subscriber<TMessageType>(aPriority)
	{
		myReceiver = std::function<ReceiveResult(const TMessageType & aMessage)>(aReceiveFunction);
	}

	template<typename TReceiveFunction, typename = std::enable_if<!std::is_same<ReceiveResult, std::result_of<TReceiveFunction>>::value>::type>
	Subscription(const TReceiveFunction & aReceiveFunction, int aPriority = 0, ReceiveResult aReturnValue = ReceiveResult::eContinue)
		: Subscriber<TMessageType>(aPriority)
	{
		TReceiveFunction receiverCopy = aReceiveFunction;
		myReceiver = std::function<ReceiveResult(const TMessageType & aMessage)>([=](const TMessageType &aMessage) -> ReceiveResult
		{
			receiverCopy(aMessage);
			return aReturnValue;
		});
	}

	ReceiveResult Receive(const TMessageType & aMessage) override;

private:
	std::function<ReceiveResult(const TMessageType & aMessage)> myReceiver;
};

template <typename TMessageType>
ReceiveResult Subscription<TMessageType>::Receive(const TMessageType& aMessage)
{
	if (myReceiver)
	{
		return myReceiver(aMessage);
	}
	return ReceiveResult::eContinue;
}

class PostMaster
{
public:
	template <typename TMessageType>
	static void Post(const TMessageType & aMessage);
};

template <typename TMessageType>
void PostMaster::Post(const TMessageType& aMessage)
{
	MessageCollection<TMessageType>::Distribute(aMessage);
}
