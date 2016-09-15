#pragma once

#include "CommonIncludes.h"

#define CheckDXError(e) { HRESULT _res = e; if (FAILED(_res)) { std::cout << #e << " (" << _res << ")" << std::endl; abort(); } }
#define SAFE_RELEASE(e) { if (e) { e->Release(); e = nullptr; } }

struct ID3D11DeviceChild;

template<UINT TNameLength>
inline void SetD3DObjectName(_In_ ID3D11DeviceChild* resource,
	_In_z_ const char(&name)[TNameLength])
{
#if defined(_DEBUG) || defined(PROFILE)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#endif
}
