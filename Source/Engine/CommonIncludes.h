#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment( lib, "dxguid.lib")

#define NOMINMAX

template<typename T>
__forceinline T max(T a, T b)
{
	return (((a) > (b)) ? (a) : (b));
}

template<typename T>
__forceinline T min(T a, T b)
{
	return (((a) < (b)) ? (a) : (b));
}

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <memory>
#include <cmath>
#include <thread>
#include <assert.h>
#include <array>
#include <atomic>
#include <mutex>

#define Error(e) { std::cout << e << std::endl; abort(); }
#define Warning(e) { std::cout << e << std::endl; }

#include "StringFormatter.h"

#include "../ModelLoader/CommonIncludes.h"

#ifdef WINDOWS
	#include <Windows.h>
	// ty windows
	#undef DrawState
	#undef GetObject
	#undef GetWindowFont
	#undef PlaySound
	#undef CreateWindow
	#undef DrawText
	#undef LoadCursor
	#undef GetMessage
#endif

static const float Pi = 3.14159265358979323846f;
static const float HalfPi = Pi / 2.f;
static const float QuarterPi = Pi / 4.f;
static const float TwoPi = Pi * 2.f;
static const float Tau = TwoPi;
static const float FullRotation = TwoPi;
static const float HalfRotation = Pi;
static const float QuarterRotation = HalfPi;

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix33.h"
#include "Matrix44.h"
#include "BoundingBox.h"
#include "Time.h"
#include "Stopwatch.h"
#include "PostMaster.h"
#include "DebugLogger.h"
#include "KeyboardKey.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "Engine.h"
