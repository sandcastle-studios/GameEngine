#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DataParser.h"
#include "rapidjson/error/en.h"

namespace ENGINE_NAMESPACE
{
	namespace DataParser
	{
		void Open(const char* aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage)
		{
			std::fstream file(aFileName);//Open file


			std::string str((std::istreambuf_iterator<char>(file)), //Begin of file
				std::istreambuf_iterator<char>()); //End of file

			size_t stringLength = str.length() + 2;
			char* data = new char[stringLength]; //Set data to the amount of characters in str

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

			rapidjson::ParseResult parseResult = aDocument.Parse(data);


			if (aDocument.HasParseError() == true)
			{
				unsigned short errorLine = 0;
				for (size_t i = 0; i < parseResult.Offset(); ++i)
				{
					if (data[i] == '\n')
					{
						++errorLine;
					}
				}

				std::string fileName = aFileName;
				std::string errorText = "Error parsing JSON file " + fileName + " at line #" + std::to_string(errorLine) + ": ";


				rapidjson::ParseErrorCode error = aDocument.GetParseError();
				switch (error)
				{
				case rapidjson::kParseErrorDocumentEmpty:
					errorText += "Document is empty";
					break;
				case rapidjson::kParseErrorDocumentRootNotSingular:
					errorText += "Document root not singular";
					break;
				case rapidjson::kParseErrorValueInvalid:
					errorText += "Value invalid";
					break;
				case rapidjson::kParseErrorObjectMissName:
					errorText += "Object missing name";
					break;
				case rapidjson::kParseErrorObjectMissColon:
					errorText += "Object missing colon";
					break;
				case rapidjson::kParseErrorObjectMissCommaOrCurlyBracket:
					errorText += "Object missing comma or curly bracket";
					break;
				case rapidjson::kParseErrorArrayMissCommaOrSquareBracket:
					errorText += "Array missing comma or square bracket";
					break;
				case rapidjson::kParseErrorStringUnicodeEscapeInvalidHex:
					errorText += "String unicode escape invalid hex";
					break;
				case rapidjson::kParseErrorStringUnicodeSurrogateInvalid:
					errorText += "String unicode surrogate invalid";
					break;
				case rapidjson::kParseErrorStringEscapeInvalid:
					errorText += "String escape invalid";
					break;
				case rapidjson::kParseErrorStringMissQuotationMark:
					errorText += "String missing quotation mark";
					break;
				case rapidjson::kParseErrorStringInvalidEncoding:
					errorText += "String invalid encoding";
					break;
				case rapidjson::kParseErrorNumberTooBig:
					errorText += "Number too big";
					break;
				case rapidjson::kParseErrorNumberMissFraction:
					errorText += "Number missing fraction";
					break;
				case rapidjson::kParseErrorNumberMissExponent:
					errorText += "Number missing exponent";
					break;
				case rapidjson::kParseErrorTermination:
					errorText += "Termination";
					break;
				case rapidjson::kParseErrorUnspecificSyntaxError:
					errorText += "Unspecified syntax error";
					break;
				default:
					errorText += "Unspecified error";
					break;
				}

				Error(errorText.c_str());
			}

			delete[] data;
			data = nullptr;

			if (aPrintLogMessage == true)
			{
				std::cout << "Loaded " << aFileName << std::endl;
			}
		}

	} namespace Data = DataParser; namespace JsonParser = DataParser; namespace Json = DataParser;
}
