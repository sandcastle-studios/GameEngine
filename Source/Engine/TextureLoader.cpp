#include "stdafx.h"
#include "TextureLoader.h"
#include "Texture.h"

std::shared_ptr<Texture> ResourceLoader<Texture>::Load(const std::string& aPath, LoadError& aError)
{
	return std::make_shared<Texture>(aPath);
}
