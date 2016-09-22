#pragma once

class AwaitableSignal
{
public:
	AwaitableSignal();
	~AwaitableSignal();

	bool Wait();
	void SignalOne();

private:
	std::atomic<bool> mySignal;
	std::mutex myMutex;
	std::condition_variable myConditionVariable;
};
