#include "stdafx.h"
#include "Engine\Debugging\CommandLineParameters.h"

namespace ENGINE_NAMESPACE
{
	CommandLineParameters * CommandLineParameters::ourInstance = nullptr;

	CommandLineParameters::CommandLineParameters()
	{
	}


	CommandLineParameters::~CommandLineParameters()
	{
	}

	void CommandLineParameters::CreateInstance()
	{
		if (ourInstance != nullptr)
		{
			Error("Already created");
		}

		ourInstance = new CommandLineParameters();
	}

	CommandLineParameters & CommandLineParameters::GetInstance()
	{
		if (ourInstance == nullptr)
		{
			Error("Not created");
		}

		return *ourInstance;
	}

	void CommandLineParameters::DestroyInstance()
	{
		if (ourInstance == nullptr)
		{
			Error("Not created");
		}

		delete ourInstance;
		ourInstance = nullptr;
	}

	void CommandLineParameters::Parse(int argc, char * argv[])
	{
		auto && currentParameterIt = myParameters.end();
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				std::string currentParameter = argv[i];
				currentParameter.erase(currentParameter.begin());

				currentParameterIt = myParameters.find(currentParameter);
				if (currentParameterIt == myParameters.end())
				{
					myParameters.emplace(currentParameter, std::unordered_set<std::string>());
					currentParameterIt = myParameters.find(currentParameter);
				}
			}
			else
			{
				if (currentParameterIt == myParameters.end())
				{
					Error("Invalid parameter format");
				}
				currentParameterIt->second.emplace(argv[i]);
			}
		}
	}

	bool CommandLineParameters::CheckParameterForValue(const std::string & aParameter, const std::string & aValue) const
	{
		auto &&parameterIt = myParameters.find(aParameter);

		if (parameterIt != myParameters.end())
		{
			auto &&valueIt = parameterIt->second.find(aValue);

			return valueIt != parameterIt->second.end();
		}

		return false;
	}

	const std::unordered_set<std::string> & CommandLineParameters::GetValuesForParameter(const std::string & aParameter)
	{
		auto &&parameterIt = myParameters.find(aParameter);

		if (parameterIt != myParameters.end())
		{
			return parameterIt->second;
		}

		myParameters.emplace(aParameter, std::unordered_set<std::string>());
		return myParameters.find(aParameter)->second;
	}
}
