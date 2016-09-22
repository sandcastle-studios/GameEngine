#pragma once

class GenericMesh;
class Effect;

enum class ModelStatus
{
	eReady,
	eNotReady,
	ePreparing
};

class Model
{
public:
	Model(const std::shared_ptr<Effect> & aEffect);
	Model(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh);
	virtual ~Model();
	
	void Render(const ::Matrix44f & aMatrix);
	void InstantRender(const ::Matrix44f & aWorldMatrix);

	const std::vector<std::shared_ptr<GenericMesh>> & GetMeshes() const;
	
	const BoundingBoxf & GetBoundingBox() const;

	virtual bool Prepare(bool aAsynchronous = true);

	void SetEffect(const std::shared_ptr<Effect> & aEffect);
	ModelStatus GetStatus() const;

protected:
	void AddMesh(const std::shared_ptr<GenericMesh> & aMesh);
	void SetStatus(ModelStatus aStatus);

private:
	std::vector<std::shared_ptr<GenericMesh>> myMeshes;
	std::shared_ptr<Effect> myEffect;
	BoundingBoxf myBoundingBox;
	ModelStatus myModelStatus;
};

inline ModelStatus Model::GetStatus() const
{
	return myModelStatus;
}
