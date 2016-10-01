#pragma once
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"

class CLoaderModel;
class CLoaderMesh;

namespace ENGINE_NAMESPACE
{
	class AssimpMesh;
	struct Vertex;

	class AssimpModel : public Model
	{
	public:
		AssimpModel(const std::string & aFilePath);
		~AssimpModel();
	private:
		void TryLoadTexture(const CLoaderModel & model, Surface & surface, const std::string & aModelDirectory, const int aLoadFromSlot, const SurfaceTextureIndex aLoadIntoSlot);
	};

	struct VertexPosColUV;

	class AssimpMesh : public Mesh<Vertex>
	{
	public:
		AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory);
	};
}
