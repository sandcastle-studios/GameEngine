#include "stdafx.h"
#include "CameraController.h"


CameraController::CameraController()
{
}


CameraControllerResult CameraController::Update(const Time & aDeltaTime, Camera & aCamera)
{
	return CameraControllerResult::eKeepControl;
}

CameraController::~CameraController()
{
}
