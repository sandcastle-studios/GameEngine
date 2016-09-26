#pragma once

struct ID3D11BlendState;

enum class BlendFactor
{
	// D3D11_BLEND_ZERO
	eZero = 1,

	// One
	eOne = 2,

	// D3D11_BLEND_SRC_COLOR
	eSourceColor = 3,
	
	// D3D11_BLEND_INV_SRC_COLOR
	eInverseSourceColor = 4,

	// D3D11_BLEND_SRC_ALPHA
	eSourceAlpha = 5,

	// D3D11_BLEND_INV_SRC_ALPHA
	eInverseSourceAlpha = 6,

	// D3D11_BLEND_DEST_ALPHA
	eDestinationAlpha = 7,

	// D3D11_BLEND_INV_DEST_ALPHA
	eInverseDestinationAlpha = 8,

	// D3D11_BLEND_DEST_COLOR
	eDestinationColor = 9,

	// D3D11_BLEND_INV_DEST_COLOR
	eInverseDestinationColor = 10,

	// D3D11_BLEND_SRC_ALPHA_SAT
	eSourceAlphaSaturate = 11,

	// D3D11_BLEND_BLEND_FACTOR
	eBlendFactor = 14,

	// D3D11_BLEND_INV_BLEND_FACTOR
	eInverseBlendFactor = 15,

	// D3D11_BLEND_SRC1_COLOR
	eSource1Color = 16,

	// D3D11_BLEND_INV_SRC1_COLOR
	eInverseSource1Color = 17,

	// D3D11_BLEND_SRC1_ALPHA
	eSourc1Alpha = 18,

	// D3D11_BLEND_INV_SRC1_ALPHA
	eInverseSource1Alpha = 19
};

enum class BlendOperation
{
	// D3D11_BLEND_OP_ADD
	eAdd = 1,

	// D3D11_BLEND_OP_SUBTRACT
	eSubtract = 2,

	// D3D11_BLEND_OP_REV_SUBTRACT
	eReverseSubtract = 3,

	// D3D11_BLEND_OP_MIN
	eMinimum = 4,

	// D3D11_BLEND_OP_MAX
	eMaximum = 5
};

enum class ColorWriteMask : uint8_t
{
	// D3D11_COLOR_WRITE_ENABLE_RED
	eWriteEnableRed = 1,

	// D3D11_COLOR_WRITE_ENABLE_GREEN
	eWriteEnableGreen = 2,

	// D3D11_COLOR_WRITE_ENABLE_BLUE
	eWriteEnableBlue = 4,

	// D3D11_COLOR_WRITE_ENABLE_ALPHA
	eWriteEnableAlpha = 8,

	// D3D11_COLOR_WRITE_ENABLE_ALL
	eWriteEnableAll = 15
};

struct BlendMode
{
	// BlendEnable
	bool blendEnable;
	// SrcBlend
    BlendFactor sourceBlend;
	// DestBlend
    BlendFactor destinationBlend;
	// BlendOp
	BlendOperation blendOperation;

	// SrcBlendAlpha
	BlendFactor sourceBlendAlpha;
	// DestBlendAlpha
	BlendFactor destinationBlendAlpha;
	// BlendOpAlpha
	BlendOperation blendOperationAlpha;

	// RenderTargetWriteMask
	ColorWriteMask renderTargetWriteMask;
};

const int MaxRenderTargets = 8;

class BlendStateDescription
{
public:
	BlendStateDescription();

	std::array<BlendMode, MaxRenderTargets> renderTarget;

	bool alphaToCoverageEnable;
	bool independentBlendEnable;

	std::array<float, 4> blendFactor;
	unsigned int sampleMask;
};

class BlendState
{
public:
	BlendState(const BlendStateDescription & aDescription);
	~BlendState();
	
	const BlendStateDescription & GetDescription() const;
	void Bind() const;

private:
	BlendStateDescription myDescription;
	ID3D11BlendState * myBlendState;
};

