#include "stdafx.h"
#include "Engine\Model\Surface.h"

void Surface::BindToPS() const
{
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eDiffuse));
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eNormal));
}

void Surface::BindSlotToPS(int aIndex) const
{
	if (myTextures[aIndex] != nullptr)
	{
		myTextures[aIndex]->BindToPS(aIndex);
	}
}

void Surface::SetSlot(const SurfaceTextureIndex aSlot, const std::shared_ptr<Texture> & aTexture)
{
	myTextures[static_cast<int>(aSlot)] = aTexture;
}
