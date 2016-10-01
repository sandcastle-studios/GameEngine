#include "stdafx.h"
#include "CameraController.h"

namespace ENGINE_NAMESPACE
{
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
}
