#pragma once

class GenericModel;

template<typename T>
class ConstantBuffer;

class ModelInstance
{
public:
	ModelInstance(std::shared_ptr<GenericModel> aModel);
	~ModelInstance();

	void Render() const;

	void SetMatrix(const Matrix44f & aMatrix);
	const Matrix44f & GetMatrix() const;

	Vector3f GetPosition() const;

	std::shared_ptr<GenericModel> GetModel();
	std::shared_ptr<const GenericModel> GetModel() const;

private:
	std::shared_ptr<GenericModel> myModel;
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

inline std::shared_ptr<GenericModel> ModelInstance::GetModel()
{
	return myModel;
}

inline std::shared_ptr<const GenericModel> ModelInstance::GetModel() const
{
	return myModel;
}
