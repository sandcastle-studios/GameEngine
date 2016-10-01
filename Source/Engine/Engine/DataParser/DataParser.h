#pragma once
#include "rapidjson\document.h"

namespace ENGINE_NAMESPACE
{
	typedef rapidjson::Document DataDocument;
	typedef rapidjson::Value& DataNode;

	namespace DataParser
	{
		void Open(const char* aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage = true);

	} namespace Data = DataParser; namespace JsonParser = DataParser; namespace Json = DataParser;
}
