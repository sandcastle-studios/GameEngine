#include "stdafx.h"
#include "AwaitableSignal.h"

AwaitableSignal::AwaitableSignal()
{
	mySignal.store(false);
}

bool AwaitableSignal::Wait()
{
	myMutex.lock();
	if (mySignal.load() == true)
	{
		myMutex.unlock();
		return false;
	}
	myMutex.unlock();

	std::unique_lock<std::mutex> lock(myMutex);
	// Wait until mySignal turns into true and then reset it to false
	myConditionVariable.wait(lock, [&]{ return mySignal.load(); });
	mySignal.store(false);
	lock.unlock();
	return true;
}

void AwaitableSignal::SignalOne()
{
	myMutex.lock();
	if (mySignal.load() == true)
	{
		myMutex.unlock();
	}
	mySignal.store(true);
	myMutex.unlock();
	myConditionVariable.notify_one();
}

AwaitableSignal::~AwaitableSignal()
{
}
