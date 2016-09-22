#pragma once

class WorkItem;
class AwaitableSignal;
class ThreadPool
{
public:
	ThreadPool();
	std::shared_ptr<WorkItem> QueueWorkItem(const std::function<void()> &aWorkItem);
	~ThreadPool();

private:
	std::vector<std::thread*> myWorkers;
	std::vector<std::shared_ptr<WorkItem>> myWork;
	std::mutex myMutex;
	std::condition_variable myConditional;
	volatile bool myIsStopping;
	int myWorkerCount;

	void WorkerThread(int workerId);
};

