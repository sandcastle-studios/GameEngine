#pragma once

struct CoutMessage;

class PostMasterSample
{
public:
	PostMasterSample();
	~PostMasterSample();

private:
	ReceiveResult MemberReceive(const CoutMessage & aMessage);
};

