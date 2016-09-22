#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	myIsStopping = false;

	unsigned int workers = std::thread::hardware_concurrency();

	if (workers == 0)
	{
		std::cout << "std::thread::hardware_concurrency() returned 0, asking Windows for system info." << std::endl;
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		workers = systemInfo.dwNumberOfProcessors;
		int processors = workers;
		if (workers > 1)
		{
			workers -= 1;
			std::cout << "Windows reported " << processors << " processors." << std::endl;
		}
		else
		{
			std::cout << "Windows reported " << processors << " processors, running in non-threaded mode" << std::endl;
			workers = 0;
		}
	}
	else
	{
		std::cout << "std::thread reported " << workers << " cores." << std::endl;

		if (workers > 1)
		{
			workers -= 1;
		}
		else
		{
			std::cout << "Single-core detected, program will run in non-threaded." << std::endl;
			workers = 0;
		}
	}

	std::cout << "Starting " << workers << " worker threads...";
	for (unsigned int i = 0; i < workers; i++)
	{
		myWorkers.push_back(new std::thread(&ThreadPool::WorkerThread, this, i + 1));
	}
	myWorkerCount = workers;
	std::cout << " Done!" << std::endl;
}

ThreadPool::~ThreadPool()
{
	myIsStopping = true;
	// Notify all threads to wake up
	myConditional.notify_all();
	for (size_t i = 0; i < myWorkers.size(); i++)
	{
		myWorkers[i]->join();
		delete myWorkers[i];
	}
	myWorkers.clear();
}

std::shared_ptr<WorkItem> ThreadPool::QueueWorkItem(const std::function<void()> &aWorkItem)
{
	std::shared_ptr<WorkItem> someWork = std::make_shared<WorkItem>(aWorkItem);
	myMutex.lock();
	if (myWorkerCount > 0)
	{
		myWork.push_back(someWork);
		// Wake one thread up so someone notices works needs to get done
		myConditional.notify_one();
	}
	else
	{
		someWork->DoWork();
	}
	myMutex.unlock();
	return someWork;
}

void ThreadPool::WorkerThread(int workerId)
{
	for (;;)
	{
		std::unique_lock<std::mutex> lock(myMutex);

		// Wait for a signal of new work
		myConditional.wait(lock);

		// Stop this worker thread
		if (myIsStopping == true)
		{
			lock.unlock();
			break;
		}

		while (myWork.size() > 0)
		{
			// Do the first work in the queue
			std::shared_ptr<WorkItem> currentWork = myWork[0];
			myWork.erase(myWork.begin());
			// Let another worker take a job
			lock.unlock();

			currentWork->DoWork();

			// Re-acquire the lock to check for more work
			lock.lock();
		}
		lock.unlock();
	}
}

