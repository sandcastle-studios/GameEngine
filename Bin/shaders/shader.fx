struct VertexInputType
{
    float4 position : POSITION;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	float2 uv : TEXCOORD;
	
	matrix toWorld : INSTANCE_MATRIX;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 worldPosition : POSITION;
	
	float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	
    float2 uv : TEXCOORD;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};


cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
	matrix toProjection;
	float4 cameraPosition;
};

cbuffer LightConstantBuffer : register(b1)
{
	struct DirectionLight
	{
		float4 direction;
		float4 color;
	} directionLight[1];
};

cbuffer LassesBuffer : register(b2)
{
	uint CubeMipCount;
	float3 trash;
}

Texture2D boundTexture : register( t0 );
Texture2D boundRoughness : register(t1);
Texture2D boundAmbientOcclusion : register(t2);
Texture2D boundEmissive : register(t3);
Texture2D boundNormalMap : register( t4 );
Texture2D boundMetalness : register(t5);
TextureCube cubeMap : register(t11);

SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);
	
	output.normal = float4(mul((float3x3)input.toWorld, input.normal.xyz), 1.0f);
	output.tangent = float4(mul((float3x3)input.toWorld, input.tangent.xyz), 1.0f);
	output.bitangent = float4(mul((float3x3)input.toWorld, input.bitangent.xyz), 1.0f);
	
	output.uv = input.uv;
	
    return output;
}

//-----------------------PIXEL SHADERUUUU

float RoughToSPow(float fRoughness)
{
	return (2.f / (fRoughness * fRoughness)) - 2.f;
}

static const float k0 = 0.00098f;
static const float k1 = 0.9921f;
static const float fakeLysMaxSpecularPower = (2.f / (0.0014f * 0.0014f)) - 2.f;
static const float fMaxT = (exp2(-10.f / sqrt((2.f / (0.0014f * 0.0014f)) - 2.f)) - 0.00098f) / 0.9921f; /* Don't know if it ends here */
float GetSpecPowToMip(float fSpecPow, int nMips)
{
	float fSmulMaxT = (exp2(-10.0f / sqrt(fSpecPow)) - k0) / k1;
	
	return float(nMips - 1 - 0) * (1.0 - clamp(fSmulMaxT / fMaxT, 0.0, 1.0));
}



PixelOutputType PixelShader_Emissive(PixelInputType input)
{
	PixelOutputType output;
	output.color.rgb = boundEmissive.Sample(samplerState, input.uv).rgb;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PixelShader_Albedo(PixelInputType input)
{
	PixelOutputType output;
	output.color.rgb = boundTexture.Sample(samplerState, input.uv).rgb;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PixelShader_Metalness(PixelInputType input)
{
	PixelOutputType output;
	output.color.rgb = boundMetalness.Sample(samplerState, input.uv).xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PixelShader_AmbientOcclusion(PixelInputType input)
{
	PixelOutputType output;
	output.color.rgb = boundAmbientOcclusion.Sample(samplerState, input.uv).xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PixelShader_Roughness(PixelInputType input)
{
	PixelOutputType output;
	output.color.rgb = boundRoughness.Sample(samplerState, input.uv).xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PixelShader_MetalnessAlbedo(PixelInputType input)
{
	PixelOutputType output;

	float3 albedo = PixelShader_Albedo(input).color.rgb;
	float3 metalness = PixelShader_Metalness(input).color.rgb;
	float3 metalnessAlbedo = albedo - (albedo * metalness);
	output.color.a = 1.f;

	output.color.rgb = metalnessAlbedo.rgb;
	return output;
}

PixelOutputType PixelShader_ObjectNormal(PixelInputType input)
{
	PixelOutputType output;
	float3 normalMap = boundNormalMap.Sample(samplerState, input.uv).xyz;
	normalMap = (normalMap * float3(2.f, 2.f, 2.f)) - float3(1.f, 1.f, 1.f);
	normalMap = normalize(normalMap);
	
	float3x3 tangentSpaceMatrix = float3x3(
		normalize(input.bitangent.xyz),
		normalize(input.tangent.xyz),
		normalize(input.normal.xyz)
	);
	
	output.color.xyz = normalize(mul(normalMap, tangentSpaceMatrix).xyz);
	output.color.a = 1.f;
	return output;
}

PixelOutputType PixelShader_Substance(PixelInputType input)
{
	float3 albedo = PixelShader_Albedo(input).color.xyz;
	float3 metalness = PixelShader_Metalness(input).color.xyz;
	float3 substance = (float3(0.04f, 0.04f, 0.04f) - (float3(0.04f, 0.04f, 0.04f) * metalness)) + albedo * metalness;

	PixelOutputType output;
	output.color.xyz = substance.xyz;
	output.color.a = 1.f;
	return output;
}


PixelOutputType PixelShader_ReflectionFresnel(PixelInputType input)
{
    float roughness = PixelShader_Roughness(input).color.x;
    float3 substance = PixelShader_Substance(input).color.xyz;
    float3 normal = PixelShader_ObjectNormal(input).color.xyz;
    float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
    float VdotN = dot(toEye.xyz, normal);

    VdotN = saturate(VdotN);
    VdotN = 1.f - VdotN;
    VdotN = pow(VdotN, 5);

    float3 fresnel = VdotN * (1.f - substance);
    fresnel = fresnel / (6 - 5 * roughness);
    fresnel = substance + fresnel;

    PixelOutputType output;
    output.color.xyz = fresnel.xyz;
    output.color.a = 1.f;
    return output;
}

PixelOutputType PixelShader_Fresnel(PixelInputType input)
{
    float3 toLight = -directionLight[0].direction.xyz;
    float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
    float3 substance = PixelShader_Substance(input).color.xyz;
    float3 halfvec = normalize(toLight + toEye.xyz);
	
    float LdotN = dot(toLight, halfvec);
    LdotN = saturate(LdotN);
    LdotN = 1.0f - LdotN;
    LdotN = pow(LdotN, 5);
	
    float3 fresnel = LdotN * (1.0f - substance);
    fresnel = substance + fresnel;
	
    PixelOutputType output;
    output.color.xyz = fresnel.xyz;
    output.color.a = 1.0f;
    return output;
}


PixelOutputType PixelShader_AmbientDiffuse(PixelInputType input)
{
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float3 metalnessAlbedo = PixelShader_MetalnessAlbedo(input).color.rgb;
	float3 ambientOcclusion = PixelShader_AmbientOcclusion(input).color.xxx;

	float3 ambientLight = cubeMap.SampleLevel(samplerState, normal.xyz, (uint) CubeMipCount.x - 2).xyz;
	float3 fresnel = PixelShader_ReflectionFresnel(input).color.xyz;

	PixelOutputType output;
	output.color.xyz = metalnessAlbedo * ambientLight * ambientOcclusion * (float3(1.f, 1.f, 1.f) - fresnel);
	output.color.a = 1.f;

	return output;
}

PixelOutputType PixelShader_AmbientSpecularity(PixelInputType input)
{
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float roughness = 0.f;
	float3 ambientOcclusion = PixelShader_AmbientOcclusion(input).color.xxx;
	
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 reflectionVector = -reflect(toEye, normal);
	
	float fakeLysSpecularPower = RoughToSPow(roughness);
	float lysMipMap = GetSpecPowToMip(fakeLysSpecularPower, (uint) CubeMipCount.x);

	float3 ambientLight = cubeMap.SampleLevel(samplerState, reflectionVector.xyz, lysMipMap).xyz;
	float3 fresnel = PixelShader_ReflectionFresnel(input).color.xyz;
	
	PixelOutputType output;
	output.color.xyz = ambientLight * ambientOcclusion * fresnel;
	output.color.a = 1.0f;
	return output;
}


PixelOutputType PixelShader_Lambert(PixelInputType input)
{
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	const float3 directionToLight = -directionLight[0].direction;	
	float lambert = saturate(dot(normal, directionToLight));

	PixelOutputType output;
	output.color.xyz = lambert.xxx;
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PixelShader_DirectDiffuse(PixelInputType input)
{
    float3 lightColor = directionLight[0].color.xyz;
	
	float3 metalnessalbedo = PixelShader_MetalnessAlbedo(input).color.xyz;
	
	float3 lambert = PixelShader_Lambert(input).color.xxx;
	float3 fresnel = PixelShader_Fresnel(input).color.xyz;
	
	PixelOutputType output;
	output.color.xyz = metalnessalbedo * lightColor * lambert * (float3(1.0f, 1.0f, 1.0f) - fresnel);
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PixelShader_Visibility(PixelInputType input)
{
    float3 toLight = -directionLight[0].direction.xyz;
	
	float roughness = PixelShader_Roughness(input).color.x;
	float roughnessRemapped = (roughness + 1.0f) / 2.0f;
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	
	float NdotL = saturate(dot(normal, toLight));
	float NdotV = saturate(dot(normal, toEye));
	
	float k = roughnessRemapped * roughnessRemapped * 1.7724f; //sqrt(PI)
	float GIV = NdotV * (1.f - k) + k;
	float GIL = NdotL * (1.f - k) + k;
	float visibility = (NdotV * NdotL) / (GIV * GIL);
	
	PixelOutputType output;
	output.color.xyz = visibility.xxx;
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PixelShader_Distribution(PixelInputType input)
{
    float3 toLight = -directionLight[0].direction.xyz;
	
	float roughness = PixelShader_Roughness(input).color.x;
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 halfvec = normalize(toLight + toEye.xyz);
	float HdotN = saturate(dot(halfvec, normal));
	
	float m = roughness * roughness;
	float m2 = m * m;
	float denominator = HdotN * HdotN * (m2 - 1.f) + 1.f;
	float distribution = m2 / (3.14159 * denominator * denominator);
	
	PixelOutputType output;
	output.color.xyz = distribution.xxx;
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PixelShader_DirectSpecularity(PixelInputType input)
{
	float3 lightColor = directionLight[0].color.xyz;
	
	float lambert = PixelShader_Lambert(input).color.xxx;
	float3 fresnel = PixelShader_Fresnel(input).color.xyz;
	float3 distribution = PixelShader_Distribution(input).color.xxx;
	float3 visibility = PixelShader_Visibility(input).color.xxx;
	
	PixelOutputType output;
	output.color.xyz = lightColor * lambert * fresnel * distribution * visibility;
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PixelShader_PBL(PixelInputType input)
{
    PixelOutputType output;
    output.color.xyz = PixelShader_AmbientSpecularity(input).color.xyz;
    output.color.a = 1.f;
    return output;

	float3 emissive = PixelShader_Emissive(input).color.xyz;
	float3 ambientDiffuse = PixelShader_AmbientDiffuse(input).color.xyz;
	float3 ambientSpecularity = PixelShader_AmbientSpecularity(input).color.xyz;

    

	float3 directDiffuse = float3(0.0f, 0.0f, 0.0f);
	float3 directSpecularity = float3(0.0f, 0.0f, 0.0f);

	for (uint i = 0; i < 1; ++i)
	{
		directDiffuse += PixelShader_DirectDiffuse(input).color.xyz;
		directSpecularity += PixelShader_DirectSpecularity(input).color.xyz;
	}

	output.color.xyz = ambientDiffuse + ambientSpecularity + directDiffuse + directSpecularity + emissive;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader(PixelInputType input)
{
	//PixelOutputType output;
	//
	//float3 sampledColor = boundTexture.Sample(samplerState, input.uv).xyz;
	////float3 sampledNormal = (boundNormalMap.Sample(samplerState, input.uv).xyz * 2.f) - (1.f).xxx;
	////
	////float3x3 tangentSpaceMatrix = float3x3(
	////	normalize(input.bitangent.xyz),
	////	normalize(input.tangent.xyz),
	////	normalize(input.normal.xyz)
	////);
	////
	////float3 normal = mul(sampledNormal, tangentSpaceMatrix);
	//
	//float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	//
	//const float3 directionToLight = -directionLight[0].direction;
	//
	//float lambert = saturate(dot(normal, directionToLight));
	//float3 directDiffuse = sampledColor * directionLight[0].color.xyz * lambert.xxx;
	//
	//float ambientAmount = 0.001f;
	//
	//output.color = float4(directDiffuse * (1.0f - ambientAmount) + sampledColor * ambientAmount, 1.0f);
	//
	//
	//return output;

	//-------------------------


	return PixelShader_PBL(input);
}
