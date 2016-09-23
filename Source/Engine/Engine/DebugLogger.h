#pragma once

class DebugLogger : public IFormattable
{
public:
	DebugLogger();
	~DebugLogger();

	template<typename ...TArgs>
	void LogInfo(const std::string & aMessage, const TArgs & ...args);

	template<typename ...TArgs>
	void LogWarning(const std::string & aMessage, const TArgs & ...args);

	template<typename ...TArgs>
	void LogError(const std::string & aMessage, const TArgs & ...args);

	template<typename ...TArgs>
	void LogResource(const std::string & aMessage, const TArgs & ...args);

	void Print(const std::string &aOutput, const std::string & aMessage);

	std::string ToString() const override;
	std::string ToString(const std::string & aFormat) const override;

	void ActivateFilterLog(const std::string & aFilter);
	void DeactivateFilterLog(const std::string & aFilter);

private:
	std::string Format(const std::string &aOutput, const std::string & aMessage);

	std::unordered_map<std::string, std::ofstream*> myOpenedFiles;
	std::ofstream * myUnfilteredLogFile;
	std::string myFileFormat;

	std::string myStartDateTime;
};

template<typename ...TArgs>
void DebugLogger::LogInfo(const std::string & aMessage, const TArgs & ...args)
{
	Print("info", FormatString(aMessage, args...));
}

template<typename ...TArgs>
void DebugLogger::LogWarning(const std::string & aMessage, const TArgs & ...args)
{
	Print("warning", FormatString(aMessage, args...));
}

template<typename ...TArgs>
void DebugLogger::LogError(const std::string & aMessage, const TArgs & ...args)
{
	Print("error", FormatString(aMessage, args...));
}

template<typename ...TArgs>
void DebugLogger::LogResource(const std::string & aMessage, const TArgs & ...args)
{
	Print("resource", FormatString(aMessage, args...));
}
