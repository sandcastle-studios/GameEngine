#pragma once

namespace ENGINE_NAMESPACE
{
	enum class FileChangeWatcherNotificationFormat
	{
		eForwardSlashes,
		eBackSlashes,
		eDefault
	};

	class FileChangeWatcher
	{
	public:
		// Pass nullptr or an empty string to myWatch working directory
		FileChangeWatcher(const wchar_t * aDirectory = nullptr, FileChangeWatcherNotificationFormat aFormat = FileChangeWatcherNotificationFormat::eForwardSlashes, float aMinimumTimeDifference = 0.1f);
		~FileChangeWatcher();

		bool PostChanges();

	private:
		void ThreadFunction(std::wstring aDirectoryToWatch, std::atomic<bool> *stopThreadFlag);

		std::thread * myThread;
		FileChangeWatcherNotificationFormat myFormat;
		std::atomic<bool> *myStopThread;
		std::unordered_map<std::string, float> lastTime;

		std::mutex myMutex;

		Stopwatch myWatch;

		struct ChangeEntry
		{
			float postTime;
			std::string file;
		};

		std::vector<ChangeEntry> myChanges;

		float myMinimumTimeDifference;
	};
}
