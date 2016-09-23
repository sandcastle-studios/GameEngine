#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment( lib, "dxguid.lib")

#include "../Utilities/CommonIncludes.h"
#include "../ModelLoader/CommonIncludes.h"

#include "StringFormatter.h"

#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Math\Vector4.h"
#include "Math\Matrix33.h"
#include "Math\Matrix44.h"
#include "Math\Quaternion.h"
#include "BoundingBox.h"
#include "Time\Time.h"
#include "Time\Stopwatch.h"
#include "PostMaster.h"
#include "DebugLogger.h"
#include "KeyboardKey.h"
#include "KeyMessages.h"
#include "ResourceManager.h"
#include "Texture\Texture.h"
#include "Texture\TextureLoader.h"
#include "Engine.h"
