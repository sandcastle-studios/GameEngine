#pragma once

namespace ENGINE_NAMESPACE
{
	class ScriptFile;

	template <>
	class ResourceLoader<ScriptFile>
	{
	public:
		static std::shared_ptr<ScriptFile> Load(const std::string & aPath, LoadError & aError);
	};

}
