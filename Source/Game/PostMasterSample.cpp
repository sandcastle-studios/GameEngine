#include "stdafx.h"
#include "PostMasterSample.h"

struct CoutMessage
{
	std::string message;
};

class CoutMessageSubscriber : public Subscriber<CoutMessage>
{
public:
	CoutMessageSubscriber(int aPriority, ReceiveResult aReceiveResult)
		: Subscriber<CoutMessage>(aPriority)
	{
		myPriority = aPriority;
		myReceiveResult = aReceiveResult;
	}

	ReceiveResult Receive(const CoutMessage& aMessage) override
	{
		std::cout << "subscriber(" << myPriority << ", " << static_cast<int>(myReceiveResult) << ") received: " << aMessage.message << std::endl;

		return myReceiveResult;
	}

private:
	int myPriority;
	ReceiveResult myReceiveResult;
};

PostMasterSample::PostMasterSample()
{
	CoutMessageSubscriber subscriber1(1, ReceiveResult::eContinue);

	{
		CoutMessageSubscriber subscriber2(0, ReceiveResult::eContinue);
		CoutMessageSubscriber subscriber3(-100, ReceiveResult::eContinue);
		CoutMessageSubscriber subscriber4(50, ReceiveResult::eContinue);

		{
			CoutMessageSubscriber subscriber5(-101, ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber6(50, ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber7(30, ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber8(20, ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber9(40, ReceiveResult::eContinue);

			Subscription<CoutMessage> subscription([](const CoutMessage & aMessage)
			{
				std::cout << "Hello from subscription!: " << aMessage.message << std::endl;
			}, 40);

			/* Does not yet work, will be implemented soon
			Subscription<CoutMessage> subscription2(std::bind(&PostMasterSample::MemberReceive, this), 40);
			*/

			PostMaster::Post(CoutMessage{ "Hello!" });
		}

		std::cout << "---" << std::endl;

		PostMaster::Post(CoutMessage{ "Hello 2!" });
	}

	std::cin.get();
}


PostMasterSample::~PostMasterSample()
{
}

ReceiveResult PostMasterSample::MemberReceive(const CoutMessage & aMessage)
{
	std::cout << "Hello from member!" << std::endl;
	return ReceiveResult::eContinue;
}
