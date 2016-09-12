#pragma once

class GenericModel;

template<typename T>
class ConstantBuffer;

class ModelInstance
{
public:
	ModelInstance(std::shared_ptr<GenericModel> aModel);
	~ModelInstance();

	void Render();

	void SetMatrix(const Matrix44f & aMatrix);
	const Matrix44f & GetMatrix();

	Vector3f GetPosition() const;
	std::shared_ptr<GenericModel> GetModel();

private:
	std::shared_ptr<GenericModel> myModel;
	std::unique_ptr<ConstantBuffer<Matrix44f>> myWorldMatrixCB;
	Matrix44f myWorldMatrix;
};

