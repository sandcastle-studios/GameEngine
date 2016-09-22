#pragma once
#include "Model.h"
#include "Mesh.h"
#include <future>

class CLoaderMesh;
class AssimpMesh;
struct Vertex;

class AssimpModel : public Model
{
public:
	AssimpModel(const std::shared_ptr<Effect> & aEffect, const std::string & aFilePath);
	~AssimpModel();

	bool Prepare(bool aAsynchronous = true) override;

private:
	void LoadModel();
	std::atomic<bool> myFinishedLoadingFlag;
	std::string myPath;
	std::function<bool()> myAsyncLoader;
};

struct VertexPosColUV;

class AssimpMesh : public Mesh<Vertex>
{
public: 
	AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory);
};
