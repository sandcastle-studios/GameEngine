#pragma once
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"

class CLoaderMesh;
class AssimpMesh;
struct Vertex;

class AssimpModel : public Model
{
public:
	AssimpModel(const std::shared_ptr<Effect> & aEffect, const char * aFilePath);
	AssimpModel(const std::shared_ptr<Effect> & aEffect, const std::string & aFilePath);
	~AssimpModel();
};

struct VertexPosColUV;

class AssimpMesh : public Mesh<Vertex>
{
public: 
	AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory);
};
