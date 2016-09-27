#pragma once
#include "rapidjson\document.h"

typedef rapidjson::Document& DataNode;

namespace DataParser
{
	void Open(const char* aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage = true);

} namespace Data = DataParser; namespace JsonParser = DataParser; namespace Json = DataParser;