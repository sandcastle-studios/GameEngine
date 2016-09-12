#pragma once

#include "CommonIncludes.h"

#define CheckDXError(e) { HRESULT _res = e; if (FAILED(_res)) { std::cout << #e << " (" << _res << ")" << std::endl; abort(); } }
#define SAFE_RELEASE(e) { if (e) { e->Release(); e = nullptr; } }
