#pragma once

enum class FileChangeWatcherNotificationFormat
{
	eForwardSlashes,
	eBackSlashes,
	eDefault
};

class FileChangeWatcher
{
public:
	// Pass nullptr or an empty string to watch working directory
	FileChangeWatcher(const wchar_t * aDirectory = nullptr, FileChangeWatcherNotificationFormat aFormat = FileChangeWatcherNotificationFormat::eForwardSlashes, float aMinimumTimeDifference = 0.1f);
	~FileChangeWatcher();

	bool QueryFileChanges(std::string & aFileName);

private:
	void ThreadFunction(std::wstring aDirectoryToWatch);

	std::thread * myThread;
	FileChangeWatcherNotificationFormat myFormat;
	std::atomic<bool> myStopThread;
	std::unordered_map<std::string, float> lastTime;

	std::mutex myMutex;
	std::queue<std::string> myQueuedChanges;

	float myMinimumTimeDifference;
};

