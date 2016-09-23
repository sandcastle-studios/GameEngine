#pragma once

class Model;

class ModelInstance
{
public:
	ModelInstance(const std::shared_ptr<Model> & aModel);
	~ModelInstance();

	void Render() const;
	void InstantRender() const;

	void SetMatrix(const Matrix44f & aMatrix);
	const Matrix44f & GetMatrix() const;

	Vector3f GetPosition() const;

	const std::shared_ptr<Model> & GetModel();
	const std::shared_ptr<const Model> & GetModel() const;

	BoundingBoxf GetBoundingBox() const;

private:
	std::shared_ptr<Model> myModel;
	Matrix44f myWorldMatrix;
};

inline const Matrix44f & ModelInstance::GetMatrix() const
{
	return myWorldMatrix;
}

inline Vector3f ModelInstance::GetPosition() const
{
	return myWorldMatrix.GetPosition();
}

inline const std::shared_ptr<Model> & ModelInstance::GetModel()
{
	return myModel;
}

inline const std::shared_ptr<const Model> & ModelInstance::GetModel() const
{
	return myModel;
}
