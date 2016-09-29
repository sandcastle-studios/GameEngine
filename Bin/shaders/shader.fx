struct VertexInput
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
	float2 uv : TEXCOORD;

	matrix toWorld : INSTANCE_MATRIX;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 worldPosition : POSITION;

	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;

	float2 uv : TEXCOORD;
};

struct PixelOutput
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

	struct PointLight
	{
		float3 position;
		float intensity;
		float3 color;
		float range;
	} pointLights[8];

	unsigned int mipMapCount;
	float3 trash;
};

#define ALBEDO_INDEX 0
#define ROUGHNESS_INDEX 1
#define AO_INDEX 2
#define EMISSIVE_INDEX 3
#define NORMAL_INDEX 4
#define METALNESS_INDEX 5

Texture2D boundTexture[6] : register(t0);
TextureCube cubemap : register(t6);

SamplerState samplerState;

PixelOutput PixelShader_Emissive(PixelInput input)
{
	PixelOutput output;
	output.color.xyz = boundTexture[EMISSIVE_INDEX].Sample(samplerState, input.uv).xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Albedo(PixelInput input)
{
	PixelOutput output;
	output.color.xyz = boundTexture[ALBEDO_INDEX].Sample(samplerState, input.uv).xyz;
	output.color.a = 1.0f;
	return output;
}

PixelOutput PixelShader_Metalness(PixelInput input)
{
	PixelOutput output;
	output.color.xyz = boundTexture[METALNESS_INDEX].Sample(samplerState, input.uv).xyz;
	output.color.a = 1.0f;
	return output;
}

PixelOutput PixelShader_Roughness(PixelInput input)
{
	PixelOutput output;
	output.color.xyz = boundTexture[ROUGHNESS_INDEX].Sample(samplerState, input.uv).xyz;
	output.color.a = 1.0f;
	return output;
}

PixelOutput PixelShader_AmbientOcclusion(PixelInput input)
{
	PixelOutput output;
	output.color.xyz = boundTexture[AO_INDEX].Sample(samplerState, input.uv).xyz;
	output.color.a = 1.0f;
	return output;
}

PixelOutput PixelShader_MetalnessAlbedo(PixelInput input)
{
	float3 albedo = PixelShader_Albedo(input).color.xyz;
	float3 metalness = PixelShader_Metalness(input).color.xyz;
	float3 metalnessAlbedo = albedo - (albedo * metalness);

	PixelOutput output;
	output.color.xyz = metalnessAlbedo.xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Normalmap(PixelInput input)
{
	PixelOutput output;
	output.color.xyz = boundTexture[NORMAL_INDEX].Sample(samplerState, input.uv).xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_ObjectNormal(PixelInput input)
{
	float3 normalmap = PixelShader_Normalmap(input).color.xyz;
	normalmap = (normalmap * float3(2.f, 2.f, 2.f)) - float3(1.f, 1.f, 1.f);
	normalmap = normalize(normalmap);

	float3 vertexNormal = input.normal.xyz;
	float3 vertexBinormal = input.bitangent.xyz;
	float3 vertexTangent = input.tangent.xyz;

	float3x3 tangentSpaceMatrix = float3x3(vertexTangent, vertexBinormal, vertexNormal);

	PixelOutput output;
	output.color.xyz = normalize(mul(normalmap, tangentSpaceMatrix).xyz);
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Visibility(PixelInput input)
{
	float3 toLight = -directionLight[0].direction.xyz;

	float roughness = PixelShader_Roughness(input).color.x;
	float roughnessRemapped = (roughness + 1.f) / 2.f;
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);

	float NdotL = saturate(dot(normal, toLight));
	float NdotV = saturate(dot(normal, toEye));

	float k = roughnessRemapped * roughnessRemapped * 1.7724f;
	float G1V = NdotV * (1.f - k) + k;
	float G1L = NdotL * (1.f - k) + k;
	float visibility = (NdotV * NdotL) / (G1V * G1L);

	PixelOutput output;
	output.color.xyz = visibility.xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Distribution(PixelInput input)
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

	PixelOutput output;
	output.color.xyz = distribution.xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Substance(PixelInput input)
{
	float3 albedo = PixelShader_Albedo(input).color.xyz;
	float3 metalness = PixelShader_Metalness(input).color.xyz;
	float3 substance = (float3(0.04f, 0.04f, 0.04f) - (float3(0.04f, 0.04f, 0.04f) * metalness)) + albedo * metalness;

	PixelOutput output;
	output.color.xyz = substance.xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_ReflectionFresnel(PixelInput input)
{
	float roughness = PixelShader_Roughness(input).color.x;
	float3 substance = PixelShader_Substance(input).color.xyz;
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float VDotN = dot(toEye.xyz, normal);
	VDotN = saturate(VDotN);
	VDotN = 1.f - VDotN;
	VDotN = pow(VDotN, 5);

	float3 fresnel = VDotN * (1.f - substance);
	fresnel = fresnel / (6 - 5 * roughness);
	fresnel = substance + fresnel;

	PixelOutput output;
	output.color.xyz = fresnel.xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_AmbientAlbedo(PixelInput input)
{
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float3 metalnessAlbedo = PixelShader_MetalnessAlbedo(input).color.xyz;
	float3 ambientOcclusion = PixelShader_AmbientOcclusion(input).color.xxx;

	float3 ambientLight = cubemap.SampleLevel(samplerState, normal.xyz, mipMapCount - 2).xyz;
	float3 fresnel = PixelShader_ReflectionFresnel(input).color.xyz;

	PixelOutput output;
	output.color.xyz = metalnessAlbedo * ambientLight * ambientOcclusion * (float3(1.f, 1.f, 1.f) - fresnel);
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Fresnel(PixelInput input)
{
	float3 toLight = -directionLight[0].direction.xyz;

	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 substance = PixelShader_Substance(input).color.xyz;
	float3 halfvec = normalize(toLight + toEye.xyz);


	float LdotH = dot(toLight, halfvec);
	LdotH = saturate(LdotH);
	LdotH = 1.0f - LdotH;
	LdotH = pow(LdotH, 5);
	float3 fresnel = LdotH * (1.f - substance);
	fresnel = substance + fresnel;

	PixelOutput output;
	output.color.xyz = fresnel.xyz;
	output.color.a = 1.f;
	return output;
}

float RoughToSPow(float aRoughness)
{
	return(2.f / (aRoughness * aRoughness)) - 2.f;
}

static const float k0 = 0.00098f;
static const float k1 = 0.9921f;
static const float fakeLysMaxSpecularPower = (2.f / (0.0014f * 0.0014f)) - 2.f;
static const float fMaxT = (exp2(-10.f / sqrt((2.f / (0.0014f * 0.0014f)) - 2.f)) - 0.00098f) / 0.9921f;
float GetSpecPowToMip(float aSpecPow, int aMips)
{
	float fSmulMaxT = (exp2(-10.0 / sqrt(aSpecPow)) - k0) / k1;

	return float(aMips - 1 - 0) * (1.0 - clamp(fSmulMaxT / fMaxT, 0.0, 1.0));
}

PixelOutput PixelShader_AmbientSpecularity(PixelInput input)
{
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	float roughness = PixelShader_Roughness(input).color.x;
	float3 ambientOcclusion = PixelShader_AmbientOcclusion(input).color.xxx;

	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 reflectionVector = -reflect(toEye, normal);

	float fakeLysSpecularPower = RoughToSPow(roughness);
	float lysMipMap = GetSpecPowToMip(fakeLysSpecularPower, mipMapCount);

	float3 ambientLight = cubemap.SampleLevel(samplerState, reflectionVector.xyz, lysMipMap).xyz;
	float3 fresnel = PixelShader_ReflectionFresnel(input).color.xyz;

	PixelOutput output;
	output.color.xyz = ambientLight * ambientOcclusion * fresnel;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_Lambert(PixelInput input)
{
	float3 normal = PixelShader_ObjectNormal(input).color.xyz;
	const float3 directionToLight = -directionLight[0].direction;
	float lambert = saturate(dot(normal, directionToLight));

	PixelOutput output;
	output.color.xyz = lambert.xxx;
	output.color.a = 1.0f;
	return output;
}

PixelOutput PixelShader_DirectAlbedo(PixelInput input)
{
	float3 lightColor = directionLight[0].color.xyz;

	float3 metalnessAlbedo = PixelShader_MetalnessAlbedo(input).color.xyz;

	float3 lambert = PixelShader_Lambert(input).color.xxx;
	float3 fresnel = PixelShader_Fresnel(input).color.xyz;

	PixelOutput output;
	output.color.xyz = metalnessAlbedo * lightColor * lambert * (float3(1.f, 1.f, 1.f) - fresnel);
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_DirectSpecularity(PixelInput input)
{
	float3 lightColor = directionLight[0].color.xyz;

	float3 lambert = PixelShader_Lambert(input).color.xxx;
	float3 fresnel = PixelShader_Fresnel(input).color.xyz;
	float3 distribution = PixelShader_Distribution(input).color.xxx;
	float3 visibility = PixelShader_Visibility(input).color.xxx;

	PixelOutput output;
	output.color.xyz = lightColor * lambert * fresnel * distribution * visibility;
	output.color.a = 1.f;
	return output;
}

PixelOutput PixelShader_PBL(PixelInput input)
{
	float3 emissive = PixelShader_Emissive(input).color.xyz;
	float3 ambientAlbedo = PixelShader_AmbientAlbedo(input).color.xyz;
	float3 ambientSpecularity = PixelShader_AmbientSpecularity(input).color.xyz;

	/////
	float3 directAlbedo = PixelShader_DirectAlbedo(input).color.xyz;
	float3 directSpecularity = PixelShader_DirectSpecularity(input).color.xyz;
	/////

	PixelOutput output;
	output.color.xyz = ambientAlbedo + ambientSpecularity + directAlbedo + directSpecularity + emissive;
	output.color.a = 1.f;
	return output;
}

PixelInput VShader(VertexInput input)
{
	PixelInput output;

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

PixelOutput PShader(PixelInput input)
{
	PixelOutput output;

	//---------------
	//Directional light

	float3 sampledAlbedo = boundTexture[ALBEDO_INDEX].Sample(samplerState, input.uv).xyz;
	float3 sampledNormal = (boundTexture[NORMAL_INDEX].Sample(samplerState, input.uv).xyz * 2.f) - (1.f).xxx;

	float3x3 tangentSpaceMatrix = float3x3(
		normalize(input.bitangent.xyz),
		normalize(input.tangent.xyz),
		normalize(input.normal.xyz)
		);

	float3 normal = mul(sampledNormal, tangentSpaceMatrix);

	const float3 directionToLight = -directionLight[0].direction;

	float3 directDiffuse = float3(0.f, 0.f, 0.f);
	float lambert = saturate(dot(normal, directionToLight));
	directDiffuse = sampledAlbedo * (directionLight[0].color.rgb) * lambert.xxx;

	float ambientAmount = 0.001f;

	//---------------
	//Point light

	for (int i = 0; i< 8; ++i)
	{
		if (pointLights[i].intensity > 0)
		{
			float3 difference = pointLights[i].position - input.worldPosition.xyz;
			float distance = length(difference);
			float3 direction = normalize(difference);

			float attenuation = saturate(1.f - (distance / pointLights[i].range));
			//avtagande funktion. Istället för 1/distance^2
			float lambert = saturate(dot(normal, direction.xyz));

			directDiffuse += sampledAlbedo.rgb * pointLights[i].color.rgb * lambert.xxx * attenuation.xxx * pointLights[i].intensity;
		}
	}

	output.color = float4(directDiffuse * (1.0f - ambientAmount) + sampledAlbedo * ambientAmount, 1.0f);

	return output;
}

PixelOutput PixelShader_Skybox(PixelInput input)
{
	float3 toPixel = normalize(input.worldPosition.xyz - cameraPosition.xyz);
	float3 ambientLight = cubemap.SampleLevel(samplerState, toPixel.xyz, 0).xyz;

	PixelOutput output;
	output.color.xyz = ambientLight;
	output.color.a = 1.f;
	return output;
}
