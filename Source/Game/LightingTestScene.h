#pragma once
#include <Scene.h>

template<typename TDataType>
class ConstantBuffer;

struct BlendCBuffer
{
	Vector4f blendColor;
};

class LightingTestScene : public Scene
{
public:
	LightingTestScene();
	~LightingTestScene();

	virtual void Render() override;

private:
	std::unique_ptr<ConstantBuffer<BlendCBuffer>> myConstantBuffer;
};
