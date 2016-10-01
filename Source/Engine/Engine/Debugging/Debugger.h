#pragma once
#include "LineVertex.h"

namespace ENGINE_NAMESPACE
{
	class Debugger
	{
	public:
		Debugger(void * aWindowHandle);
		~Debugger();

		void NewFrame();
		void RenderFrame();

		void DrawLine(const Vector3f & aFrom, const Vector3f & aTo, const Vector4f & aColor);

	private:
		std::shared_ptr<Effect> myLineEffect;
		std::shared_ptr<VertexBuffer<LineVertex>> myLineVertexBuffer;
	};
}
