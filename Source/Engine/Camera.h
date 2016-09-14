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

	void SetPitch(float aPitch);
	void AddPitch(float aPitchToAdd);
	float GetPitch() const;

	void SetYaw(float aPitch);
	void AddYaw(float aYawToAdd);
	float GetYaw() const;
	void LookAt(const Vector3f & aLookAt);

	const ConstantBuffer<CameraCB> & GetCameraConstantBuffer() const;

	void ApplyToVS() const;

	void UpdateCB() const;

private:
	std::unique_ptr<ConstantBuffer<CameraCB>> myCameraCB;
	Vector3f myPosition;
	float myYaw;
	float myPitch;
	Matrix44f myProjection;
public:
	void ApplySkyboxMatrixToVS() const;
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

inline void Camera::SetPitch(float aPitch)
{
	myPitch = aPitch;
}

inline void Camera::AddPitch(float aPitchToAdd)
{
	myPitch += aPitchToAdd;
}

inline float Camera::GetPitch() const
{
	return myPitch;
}

inline void Camera::SetYaw(float aYaw)
{
	myYaw = aYaw;
}

inline void Camera::AddYaw(float aYawToAdd)
{
	myYaw += aYawToAdd;
}

inline float Camera::GetYaw() const
{
	return myYaw;
}