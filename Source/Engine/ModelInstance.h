#pragma once

class Model;

template<typename T>
class ConstantBuffer;

class ModelInstance
{
public:
	ModelInstance(std::shared_ptr<Model> aModel);
	~ModelInstance();

	void Render() const;

	void SetMatrix(const Matrix44f & aMatrix);
	const Matrix44f & GetMatrix() const;

	Vector3f GetPosition() const;

	std::shared_ptr<Model> GetModel();
	std::shared_ptr<const Model> GetModel() const;

private:
	std::shared_ptr<Model> myModel;
	// std::unique_ptr<ConstantBuffer<Matrix44f>> myWorldMatrixCB;
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

inline std::shared_ptr<Model> ModelInstance::GetModel()
{
	return myModel;
}

inline std::shared_ptr<const Model> ModelInstance::GetModel() const
{
	return myModel;
}
