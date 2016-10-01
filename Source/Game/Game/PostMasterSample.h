#pragma once

struct CoutMessage;

class PostMasterSample
{
public:
	PostMasterSample();
	~PostMasterSample();

private:
	SB::ReceiveResult MemberReceive(const CoutMessage & aMessage);
};

