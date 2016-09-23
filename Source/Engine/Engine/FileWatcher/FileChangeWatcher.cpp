#include "stdafx.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"
#include "Engine\Time\Stopwatch.h"

FileChangeWatcher::FileChangeWatcher(const wchar_t * aDirectory, FileChangeWatcherNotificationFormat aFormat, float aMinimumTimeDifference)
{
	myFormat = aFormat;
	myMinimumTimeDifference = aMinimumTimeDifference;

	std::wstring directoryToWatch;
	
	if (aDirectory == nullptr || wcslen(aDirectory) == 0)
	{
		wchar_t buffer[MAX_PATH];
		if (GetCurrentDirectoryW(MAX_PATH, buffer) == 0)
		{
			std::cout << "FileChangeWatcher failed to find the working directory. You will not be notified of changes." << std::endl;
			myThread = nullptr;
			return;
		}
		directoryToWatch = buffer;
	}
	else
	{
		directoryToWatch = aDirectory;
	}

	myStopThread = new std::atomic<bool>();
	myStopThread->store(false);
	myThread = new std::thread(std::bind(&FileChangeWatcher::ThreadFunction, this, directoryToWatch, myStopThread));
}

FileChangeWatcher::~FileChangeWatcher()
{
	myStopThread->store(true);

	/* =(
	
	if (myThread != nullptr)
	{
		myThread->join();
		delete myThread;
		myThread = nullptr;
	}*/
}

bool FileChangeWatcher::PostChanges()
{
	std::lock_guard<std::mutex> lock(myMutex);
	for (size_t i=0; i<myChanges.size(); i++)
	{
		PostMaster::Post(FileChangedEvent(myChanges[i]));
	}
	myChanges.clear();
	return true;
}


void FileChangeWatcher::ThreadFunction(std::wstring aDirectoryToWatch, std::atomic<bool> *stopThreadFlag)
{
	HANDLE directory = CreateFile(aDirectoryToWatch.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr,
		OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
	
	if (directory == INVALID_HANDLE_VALUE)
	{
		Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
		return;
	}

	/*HANDLE waitHandle = FindFirstChangeNotification(aDirectoryToWatch.c_str(), true, FILE_NOTIFY_CHANGE_LAST_WRITE);

	if (waitHandle == INVALID_HANDLE_VALUE)
	{
		Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
		return;
	}*/

	FILE_NOTIFY_INFORMATION notifications[255];
	Stopwatch watch;

	while (stopThreadFlag->load() == false)
	{
		/*DWORD waitStatus = WaitForSingleObject(waitHandle, 250);

		switch (waitStatus)
		{
		case WAIT_OBJECT_0:
			if (FindNextChangeNotification(waitHandle) == false)
			{
				Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
				return;
			}
			break;

		case WAIT_TIMEOUT:
			// Continue waiting
			continue;

		case WAIT_FAILED:
			Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
			return;
		}*/

		FILE_NOTIFY_INFORMATION * current = notifications;
		DWORD bytesReturned;

		if (ReadDirectoryChangesW(directory, notifications, sizeof(notifications), true, FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, nullptr, nullptr))
		{
			if (stopThreadFlag->load() == true)
			{
				return;
			}

			for (;;)
			{
				std::vector<wchar_t> data;
				data.resize(current->FileNameLength + sizeof(wchar_t));
				memcpy(&data[0], current->FileName, current->FileNameLength);
				data[data.size() - sizeof(wchar_t)] = L'\0';

				std::string fileName;

				if (myFormat == FileChangeWatcherNotificationFormat::eDefault)
				{
					fileName = std::string(data.begin(), data.end());
				}
				else
				{
					fileName.resize((data.size() / sizeof(wchar_t)) - 1);

					for (size_t i = 0; i < fileName.size(); i++)
					{
						if (data[i] == L'\\')
						{
							if (myFormat == FileChangeWatcherNotificationFormat::eForwardSlashes)
							{
								fileName[i] = '/';
								continue;;
							}
						}
						else if (data[i] == '/')
						{
							if (myFormat == FileChangeWatcherNotificationFormat::eBackSlashes)
							{
								fileName[i] = '\\';
								continue;
							}
						}

						fileName[i] = static_cast<char>(data[i]);
					}
				}

				auto currentTime = watch.GetElapsedTime().InSeconds();
				auto &&lastTimeIt = lastTime.find(fileName);

				if (lastTime.find(fileName) == lastTime.end() ||
					currentTime > lastTimeIt->second + myMinimumTimeDifference)
				{
					std::lock_guard<std::mutex> lock(myMutex);

					myChanges.push_back(fileName);

					lastTime[fileName] = currentTime;
				}

				if (current->NextEntryOffset == 0)
				{
					break;
				}

				current = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<char*>(current) + current->NextEntryOffset);
			}
		}
		else
		{
			Sleep(250);
		}
	}

	//FindCloseChangeNotification(waitHandle);
}
