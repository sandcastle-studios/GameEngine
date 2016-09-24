#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment( lib, "dxguid.lib")
#pragma comment( lib, "../../extlibs/imgui/lib/imgui.lib")

#include "Utilities/CommonIncludes.h"
#include "../ModelLoader/CommonIncludes.h"

#include "Engine\StringFormatter.h"


#include "Engine\BoundingBox.h"
#include "Engine\Time\Time.h"
#include "Engine\Time\Stopwatch.h"
#include "Engine\PostMaster.h"
#include "Engine\Debugging\DebugLogger.h"
#include "Engine\Input\KeyboardKey.h"
#include "Engine\Input\KeyMessages.h"
#include "Engine\Resources\ResourceManager.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Texture\TextureLoader.h"
#include "Engine\Engine.h"
#include "Engine\Buffer\Buffer.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Buffer\ShaderResourceBuffer.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Model\Model.h"
#include "Engine\Sprite\Sprite.h"
#include "Engine\Debugging\Debugger.h"
