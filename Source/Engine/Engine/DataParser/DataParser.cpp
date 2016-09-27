#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DataParser.h"

namespace DataParser
{
	void Open(const char* aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage)
	{
		std::fstream file(aFileName);//Open file

		if (aPrintLogMessage == true)
		{
			std::cout << "Opened " << aFileName << std::endl;
		}

		std::string str((std::istreambuf_iterator<char>(file)), //Begin of file
			std::istreambuf_iterator<char>()); //End of file

		char* data = new char[str.length() + 2]; //Set data to the amount of characters in str

		unsigned int dataIndex = 0;
		for (unsigned int i = 0; i < str.length(); ++i)
		{
			if (str[i] != 0)
			{
				data[dataIndex] = str[i];
				++dataIndex;
			}
		}

		data[dataIndex] = '\0'; //Set last character to null
		file.close();//Close file

		aDocument.Parse(data);

		if (aDocument.HasParseError() == true)
		{
			std::string fileName = aFileName;
			std::string errorText = "JSON-file could not be loaded. Did you spell the path correctly? Or missing ','. File is " + fileName;
			assert(errorText.c_str());
		}

		delete[] data;
		data = nullptr;
	}

} namespace Data = DataParser; namespace JsonParser = DataParser; namespace Json = DataParser;