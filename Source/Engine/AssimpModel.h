#pragma once
#include "Model.h"
#include "Mesh.h"

class CLoaderMesh;
class AssimpMesh;

class AssimpModel : public Model
{
public:
	AssimpModel(std::shared_ptr<Effect> aEffect, const char * aFilePath);
	AssimpModel(std::shared_ptr<Effect> aEffect, const std::string & aFilePath);
	~AssimpModel();
};

struct VertexPosColUV;

class AssimpMesh : public Mesh<VertexPosColUV>
{
public: 
	AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory);
};
