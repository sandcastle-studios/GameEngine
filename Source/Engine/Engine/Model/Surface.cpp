#include "stdafx.h"
#include "Engine\Model\Surface.h"

namespace ENGINE_NAMESPACE
{

	Surface::Surface()
	{
		myTextures[static_cast<int>(SurfaceTextureIndex::eDiffuse)] = Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_al.dds");
		myTextures[static_cast<int>(SurfaceTextureIndex::eAmbientOcclusion)] = Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_ao.dds");
		myTextures[static_cast<int>(SurfaceTextureIndex::eEmissive)] = Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_em.dds");
		myTextures[static_cast<int>(SurfaceTextureIndex::eMetalness)] = Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_me.dds");
		myTextures[static_cast<int>(SurfaceTextureIndex::eNormal)] = Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_no.dds");
		myTextures[static_cast<int>(SurfaceTextureIndex::eRoughness)] = Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_ro.dds");
	}

	void Surface::BindToPS() const
	{
		for (int i = 0; i < static_cast<int>(SurfaceTextureIndex::eCount); i++)
		{
			BindSlotToPS(i);
		}
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
}
