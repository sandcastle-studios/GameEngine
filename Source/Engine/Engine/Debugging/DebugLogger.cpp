#include "stdafx.h"
#include "Engine\Debugging\DebugLogger.h"
#include <fstream>
#include "Engine\Debugging\CommandLineParameters.h"

namespace ENGINE_NAMESPACE
{
	DebugLogger::DebugLogger()
	{
		LogInfo("Debug Logger is starting");

		myFileFormat = "logs/{0:startDateTime}_{1}.log";

		time_t t = time(nullptr);
		tm t2;
		localtime_s(&t2, &t);
		myStartDateTime = FormatString("{0}-{1}-{2} {3}'{4}'{5}", 1900 + t2.tm_year, t2.tm_mon, t2.tm_mday, t2.tm_hour, t2.tm_min, t2.tm_sec);

		CreateDirectoryA("logs", nullptr);

		if (CommandLineParameters::GetInstance().CheckParameterForValue("disable-log", "all") == false)
		{
			myUnfilteredLogFile = new std::ofstream(FormatString(myFileFormat, *this, "all"), std::ofstream::out | std::ofstream::app);
		}
		else
		{
			myUnfilteredLogFile = nullptr;
		}

		for (auto && log : CommandLineParameters::GetInstance().GetValuesForParameter("enable-log"))
		{
			ActivateFilterLog(log);
			LogInfo("Log Filter \"{0}\" is now enabled for seperate log output.", log);
		}
	}

	DebugLogger::~DebugLogger()
	{
		LogInfo("Debug Logger is shutting down");

		for (auto && it = myOpenedFiles.begin(); it != myOpenedFiles.end(); ++it)
		{
			it->second->flush();
			delete it->second;
		}
		myOpenedFiles.clear();

		delete myUnfilteredLogFile;
		myUnfilteredLogFile = nullptr;
	}

	void DebugLogger::Print(const std::string &aOutput, const std::string & aMessage)
	{
		auto &&it = myOpenedFiles.find(aOutput);
		std::ofstream *out = nullptr;

		if (it != myOpenedFiles.end())
		{
			out = it->second;
		}

		std::string finishedOutput = Format(aOutput, aMessage);

		if (out != nullptr)
		{
			*out << finishedOutput << std::endl;
		}

		if (myUnfilteredLogFile != nullptr)
		{
			*myUnfilteredLogFile << finishedOutput << std::endl;
		}

		std::cout << finishedOutput << std::endl;
	}

	std::string DebugLogger::Format(const std::string &aOutput, const std::string & aMessage)
	{
		time_t t = time(nullptr);
		tm t2;
		localtime_s(&t2, &t);

		return FormatString("[{1}:{2}:{3}] {0}: {4}", aOutput, t2.tm_hour, t2.tm_min, t2.tm_sec, aMessage);
	}

	std::string DebugLogger::ToString() const
	{
		return "[DebugLogger]";
	}

	std::string DebugLogger::ToString(const std::string & aFormat) const
	{
		if (aFormat == "startDateTime")
		{
			return myStartDateTime;
		}

		return FormatString("[DebugLogger{0}]", aFormat);
	}

	void DebugLogger::ActivateFilterLog(const std::string & aFilter)
	{
		auto &&it = myOpenedFiles.find(aFilter);

		if (it == myOpenedFiles.end())
		{
			std::ofstream *out = new std::ofstream(FormatString(myFileFormat, *this, aFilter), std::ofstream::out | std::ofstream::app);
			myOpenedFiles.emplace(aFilter, out);
		}
	}

	void DebugLogger::DeactivateFilterLog(const std::string & aFilter)
	{
		auto &&it = myOpenedFiles.find(aFilter);

		if (it != myOpenedFiles.end())
		{
			it->second->flush();
			delete it->second;
			myOpenedFiles.erase(it);
		}
	}
}
