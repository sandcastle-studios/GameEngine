#pragma once
#include "ResourceManager.h"

class Texture;

template<>
class ResourceLoader<Texture>
{
public:
	static std::shared_ptr<Texture> Load(const std::string & aPath, LoadError & aError);
};

