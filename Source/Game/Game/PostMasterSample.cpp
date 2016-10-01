#include "stdafx.h"
#include "PostMasterSample.h"

struct CoutMessage
{
	std::string message;
};

class CoutMessageSubscriber : public SB::Subscriber<CoutMessage>
{
public:
	CoutMessageSubscriber(int aPriority, SB::ReceiveResult aReceiveResult)
		: SB::Subscriber<CoutMessage>(aPriority)
	{
		myPriority = aPriority;
		myReceiveResult = aReceiveResult;
	}

	SB::ReceiveResult Receive(const CoutMessage& aMessage) override
	{
		std::cout << "subscriber(" << myPriority << ", " << static_cast<int>(myReceiveResult) << ") received: " << aMessage.message << std::endl;

		return myReceiveResult;
	}

private:
	int myPriority;
	SB::ReceiveResult myReceiveResult;
};

PostMasterSample::PostMasterSample()
{
	CoutMessageSubscriber subscriber1(1, SB::ReceiveResult::eContinue);

	{
		CoutMessageSubscriber subscriber2(0, SB::ReceiveResult::eContinue);
		CoutMessageSubscriber subscriber3(-100, SB::ReceiveResult::eContinue);
		CoutMessageSubscriber subscriber4(50, SB::ReceiveResult::eContinue);

		{
			CoutMessageSubscriber subscriber5(-101, SB::ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber6(50, SB::ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber7(30, SB::ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber8(20, SB::ReceiveResult::eContinue);
			CoutMessageSubscriber subscriber9(40, SB::ReceiveResult::eContinue);

			SB::Subscription<CoutMessage> subscription([](const CoutMessage & aMessage)
			{
				std::cout << "Hello from subscription!: " << aMessage.message << std::endl;
			}, 40);

			/* Does not yet work, will be implemented soon
			Subscription<CoutMessage> subscription2(std::bind(&PostMasterSample::MemberReceive, this), 40);
			*/

			SB::PostMaster::Post(CoutMessage{ "Hello!" });
		}

		std::cout << "---" << std::endl;

		SB::PostMaster::Post(CoutMessage{ "Hello 2!" });
	}

	std::cin.get();
}


PostMasterSample::~PostMasterSample()
{
}

SB::ReceiveResult PostMasterSample::MemberReceive(const CoutMessage & aMessage)
{
	std::cout << "Hello from member!" << std::endl;
	return SB::ReceiveResult::eContinue;
}
