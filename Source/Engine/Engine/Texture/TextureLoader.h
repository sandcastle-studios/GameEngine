#pragma once
#include "Engine\Resources\ResourceManager.h"

class Texture;

template<>
class ResourceLoader<Texture>
{
public:
	static std::shared_ptr<Texture> Load(const std::string & aPath, LoadError & aError);
};

