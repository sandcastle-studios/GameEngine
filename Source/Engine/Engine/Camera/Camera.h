#pragma once

template<typename T>
class ConstantBuffer;

struct CameraCB
{
	Matrix44f view;
	Matrix44f projection;
	Vector4f cameraPosition;
};

class Camera
{
public:
	Camera();
	~Camera();

	void CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane);

	void SetPosition(const Vector3f & aPosition);
	void AddPosition(const Vector3f & aPositionToAdd);
	const Vector3f & GetPosition() const;

	void LookAt(const Vector3f & aLookAt);

	Quaternion& GetRototation();
	const Quaternion& GetRototation() const;

	const ConstantBuffer<CameraCB> & GetCameraConstantBuffer() const;

	void ApplyToVS() const;
	void ApplySkyboxMatrixToVS() const;

	void UpdateCB() const;

private:
	std::unique_ptr<ConstantBuffer<CameraCB>> myCameraCB;
	Vector3f myPosition;
	Quaternion myRotation;
	Matrix44f myProjection;
};


inline void Camera::SetPosition(const Vector3f & aPosition)
{
	myPosition = aPosition;
}

inline void Camera::AddPosition(const Vector3f & aPositionToAdd)
{
	myPosition += aPositionToAdd;
}

inline const Vector3f & Camera::GetPosition() const
{
	return myPosition;
}

inline Quaternion & Camera::GetRototation()
{
	return myRotation;
}

inline const Quaternion & Camera::GetRototation() const
{
	return myRotation;
}
