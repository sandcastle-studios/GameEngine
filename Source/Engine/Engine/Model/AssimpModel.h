#pragma once
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"

class CLoaderModel;
class CLoaderMesh;
class AssimpMesh;
struct Vertex;

class AssimpModel : public Model
{
public:
	AssimpModel(const std::shared_ptr<Effect> & aEffect, const char * aFilePath);
	AssimpModel(const std::shared_ptr<Effect> & aEffect, const std::string & aFilePath);
	~AssimpModel();
private:
	void TryLoadTexture(const CLoaderModel & model, Surface & surface, const std::string & aModelDirectory, const int aLoadFromSlot, const SurfaceTextureIndex aLoadIntoSlot);
};

struct VertexPosColUV;

class AssimpMesh : public Mesh<Vertex>
{
public: 
	AssimpMesh(const std::shared_ptr<Effect> & aEffect, CLoaderMesh * aMesh, const std::string & aModelDirectory);
};
