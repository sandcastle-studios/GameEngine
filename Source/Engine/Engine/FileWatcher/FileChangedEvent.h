#pragma once

namespace ENGINE_NAMESPACE
{
	class FileChangedEvent
	{
	public:
		FileChangedEvent(const std::string &aPath);
		~FileChangedEvent();

		const std::string& GetPath() const;

	private:
		std::string myPath;
	};

	inline const std::string& FileChangedEvent::GetPath() const
	{
		return myPath;
	}
}
