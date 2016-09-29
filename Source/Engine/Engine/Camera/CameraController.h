#pragma once
#include "Engine/Camera/Camera.h"

enum class CameraControllerResult
{
	eKeepControl,
	ePassControl
};

class CameraController
{
public:
	virtual CameraControllerResult Update(const Time & aDeltaTime, Camera & aCamera) = 0;
	virtual ~CameraController();

protected:
	CameraController();
};

