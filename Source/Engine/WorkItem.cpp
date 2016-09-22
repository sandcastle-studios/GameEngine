#include "stdafx.h"
#include "WorkItem.h"

WorkItem::WorkItem(const std::function<void()> &aWork)
{
	mySignal = new AwaitableSignal();
	myWork = new std::function<void()>(aWork);
}

WorkItem::WorkItem(WorkItem &&aWorkItem)
{
	mySignal = aWorkItem.mySignal;
	myWork = aWorkItem.myWork;
	aWorkItem.mySignal = nullptr;
	aWorkItem.myWork = nullptr;
}

WorkItem &WorkItem::operator=(WorkItem &&aWorkItem)
{
	mySignal = aWorkItem.mySignal;
	myWork = aWorkItem.myWork;
	aWorkItem.mySignal = nullptr;
	aWorkItem.myWork = nullptr;
	return *this;
}

void WorkItem::DoWork()
{
	(*myWork)();
	mySignal->SignalOne();
}

void WorkItem::Wait()
{
	mySignal->Wait();
}

WorkItem::~WorkItem()
{
	delete mySignal;
	mySignal = nullptr;
	delete myWork;
	myWork = nullptr;
}

