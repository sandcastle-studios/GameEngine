#pragma once

class WorkItem
{
public:
	WorkItem(const std::function<void()> &aWork);
	WorkItem(WorkItem &&aWorkItem);
	~WorkItem();

	WorkItem &operator=(WorkItem &&aWorkItem);

	void Wait();
	void DoWork();

private:
	AwaitableSignal *mySignal;
	std::function<void()> *myWork;
};
