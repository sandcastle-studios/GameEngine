#pragma once

class IFormattable
{
public:
	virtual std::string ToString() const = 0
	{
		return "";
	}

	virtual std::string ToString(const std::string &aFormat) const = 0
	{
		return "";
	}

	virtual ~IFormattable()
	{
	}
};

template<typename T>
inline typename std::enable_if<std::is_base_of<IFormattable, T>::value == true, std::string>::type MakeString(const T &aValue)
{
	return aValue.ToString();
}

template<typename T>
inline typename std::enable_if<std::is_base_of<IFormattable, T>::value == false, std::string>::type MakeString(const T &aValue)
{
	return std::to_string(aValue);
}

inline std::string MakeString(const std::string &aValue)
{
	return aValue;
}

inline std::string MakeString(const char *aValue)
{
	return aValue;
}

template<typename T>
inline typename std::enable_if<std::is_base_of<IFormattable, T>::value == true, std::string>::type MakeString(const T &aValue, const std::string &aFormat)
{
	return aValue.ToString(aFormat);
}

template<typename T>
inline typename std::enable_if<std::is_base_of<IFormattable, T>::value == false, std::string>::type MakeString(const T &aValue, const std::string &aFormat)
{
	return std::to_string(aValue);
}

inline std::string MakeString(const std::string &aValue, const std::string &aFormat)
{
	return aValue;
}

inline std::string MakeString(const char *aValue, const std::string &aFormat)
{
	return aValue;
}

template <typename T, typename ...values>
inline std::string MakeArgument(int number, const std::string &aFormat, const T &aValue)
{
	if (number != 0)
	{
		Error("String format index out of range!");
	}
	return MakeString(aValue, aFormat);
}

template <typename T, typename ...values>
inline std::string MakeArgument(int number, const std::string &aFormat, const T &aValue, const values& ...someValues)
{
	if (number == 0)
	{
		return MakeString(aValue, aFormat);
	}
	return MakeArgument(number - 1, aFormat, someValues...);
}

inline std::string FormatString(const std::string &aFormat)
{
	return aFormat;
}

template<typename... values>
inline std::string FormatString(const std::string &aFormat, const values& ...someValues)
{
	std::string formattedString = aFormat;

	bool isInsideBracket = false;
	size_t bracketStart = 0;
	std::string bracketsContent;
	std::string propertyContent;
	bool isInProperty = false;

	for (size_t i = 0; i < formattedString.size(); i++)
	{
		if (formattedString[i] == '{')
		{
			if (isInsideBracket == true)
			{
				Error("Format error, two start brackets found in a row");
			}
			isInsideBracket = true;
			bracketStart = i;
		}
		else if (isInsideBracket == true)
		{
			if (formattedString[i] == '}')
			{
				if (isInsideBracket == false)
				{
					Error("Format error, end bracket found with no start bracket");
				}
				isInsideBracket = false;

				int argumentNumber = std::stoi(bracketsContent);
				const std::string str = MakeArgument(argumentNumber, propertyContent, someValues...);

				formattedString.replace(formattedString.begin() + bracketStart, formattedString.begin() + i + 1, str);
				i -= static_cast<int>(i - bracketStart) - static_cast<int>(str.size());

				bracketsContent.clear();
				propertyContent.clear();
				isInProperty = false;
			}
			else if (formattedString[i] == ':')
			{
				if (isInProperty == true)
				{
					Error("Format error, already in property");
				}
				isInProperty = true;
			}
			else
			{
				if (isInProperty)
				{
					propertyContent.push_back(formattedString[i]);
				}
				else
				{
					bracketsContent.push_back(formattedString[i]);
				}
			}
		}
	}

	return formattedString;
}

template<typename T>
inline std::string Concatenate(const T &aValue)
{
	return MakeString(aValue);
}

template<typename T, typename... values>
inline std::string Concatenate(const T &aValue, const values& ...someValues)
{
	return MakeString(aValue) + Concatenate(someValues...);
}
