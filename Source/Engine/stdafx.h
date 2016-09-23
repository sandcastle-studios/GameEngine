#pragma once

#include "Engine\CommonIncludes.h"

#define SAFE_RELEASE(e) { if (e) { e->Release(); e = nullptr; } }

#define DX_ERROR_MESSAGE_BOX(errorMessage, errorCode, line)	\
			LPVOID pText = 0;	\
::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,	\
	NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&pText, 0, NULL);	\
LPCWSTR errorNumber = (LPCWSTR)pText;	\
std::string lineNumber = " At Line: " + std::to_string(line) ;	\
std::string fileName = __FILE__; \
std::string fileNameInfo = "At file: ";	\
std::wstring finalString = std::wstring(errorMessage.begin(), errorMessage.end()) + std::wstring(errorNumber) + std::wstring(fileNameInfo.begin(), fileNameInfo.end()) + \
std::wstring(fileName.begin(), fileName.end()) + std::wstring(lineNumber.begin(), lineNumber.end());	\
LPCWSTR sw = finalString.c_str();	\
MessageBox(NULL, sw, 0, MB_OK);	\
LocalFree(pText);

#define CheckDXError(e) { HRESULT _res = e; size_t line = __LINE__; if (FAILED(_res)) { std::string em = std::string("Error at:\r\n\r\n") + std::string(#e) + std::string("\r\n\r\n"); DX_ERROR_MESSAGE_BOX(em, _res, line); abort(); } }

struct ID3D11DeviceChild;

template<UINT TNameLength>
inline void SetD3DObjectName(_In_ ID3D11DeviceChild* resource,
	_In_z_ const char(&name)[TNameLength])
{
#if defined(_DEBUG) || defined(PROFILE)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#endif
}
