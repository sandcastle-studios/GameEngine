#include "common.fx"
#include "lys.fx"

static float3 gLightDirection;

static PixelInput gInput;
static float3 gToLight;
static float3 gToEye;
static float3 gHalfVec;
static float3 gAlbedo;
static float3 gObjectNormal;
static float gRoughness;
static float gMetalness;
static float gAmbientOcclusion;
static float3 gEmissive;
static float3 gMetalnessAlbedo;
static float3 gSubstance;
static float3 gFresnel;
static float3 gReflectionFresnel;
static float3 gDistribution;
static float gVisibility;
static float3 gAmbientDiffuse;
static float3 gAmbientSpecularity;
static float3 gLambert;

void CalculateFresnel()
{
	float LdotN = dot(gToLight, gHalfVec);
	LdotN = saturate(LdotN);
	LdotN = 1.0f - LdotN;
	LdotN = pow(LdotN, 5.0f);

	gFresnel = LdotN * (1.0f - gSubstance);
	gFresnel = gSubstance + gFresnel;
}

void CalculateReflectionFresnel()
{
	float VdotN = dot(gToEye, gObjectNormal);
	VdotN = saturate(VdotN);
	VdotN = 1.0f - VdotN;
	VdotN = pow(VdotN, 5.0f);

	gReflectionFresnel = VdotN * (1.0f - gSubstance);
	gReflectionFresnel = gReflectionFresnel / (6 - 5 * gRoughness);
	gReflectionFresnel = gSubstance + gReflectionFresnel;
}

void CalculateDistribution()
{
	float HdotN = saturate(dot(gHalfVec, gObjectNormal));
	float m = gRoughness * gRoughness;
	float m2 = m * m;
	float denominator = HdotN * HdotN * (m2 - 1.f) + 1.f;
	gDistribution = m2 / (Pi * denominator * denominator);
}

void CalculateVisibility()
{
	float roughnessRemapped = (gRoughness + 1.0f) / 2.0f;

	float NdotV = saturate(dot(gObjectNormal, gToEye));
	float NdotL = saturate(dot(gObjectNormal, gToLight));

	float k = roughnessRemapped * roughnessRemapped * 1.7724f; // sqrt(Pi)
	float GIV = NdotV * (1.f - k) + k;
	float GIL = NdotL * (1.f - k) + k;
	gVisibility = (NdotV * NdotL) / (GIV * GIL);
}

void CalculateAmbientDiffuse()
{
	float3 ambientLight = boundCubeMap.SampleLevel(samplerState, gObjectNormal, 8).xyz;
	gAmbientDiffuse = gMetalnessAlbedo * ambientLight * gAmbientOcclusion * (float3(1.0f, 1.0f, 1.0f) - gReflectionFresnel);
}

void CalculateAmbientSpecularity()
{
	float3 reflectionVector = -reflect(gToEye, gObjectNormal);
	float fakeLysSpecularPower = RoughToSPow(gRoughness);
	float lysMipMap = GetSpecPowToMip(fakeLysSpecularPower, 8);
    float3 ambientLight = boundCubeMap.SampleLevel(samplerState, reflectionVector.xyz, lysMipMap).xyz;
	gAmbientSpecularity = ambientLight * gAmbientOcclusion * gReflectionFresnel;
}

float3 CalulateDirectDiffuse(float3 aLightColor)
{
	return gMetalnessAlbedo * aLightColor * gLambert * (float3(1.0f, 1.0f, 1.0f) - gFresnel);
}

float3 CalulateDirectSpecularity(float3 aLightColor)
{
	return aLightColor * gLambert * gFresnel * gDistribution * gVisibility;
}

PixelOutput PShader(PixelInput aInput)
{
	gInput = aInput;
	
	gLightDirection = normalize(directionLight[0].direction.xyz);
	
    gToEye = normalize(cameraPosition.xyz - gInput.worldPosition.xyz);
	gToLight = -gLightDirection;
	gHalfVec = normalize(gToLight + gToEye);

	gAlbedo = boundTexture.Sample(samplerState, gInput.uv).xyz;
	float3 normalMap = (boundNormalMap.Sample(samplerState, gInput.uv).xyz * 2.f) - (1.f).xxx;
    gObjectNormal = normalize(mul(normalMap, float3x3(gInput.tangent.xyz, gInput.bitangent.xyz, gInput.normal.xyz)).xyz);
	gRoughness = boundRoughnessMap.Sample(samplerState, gInput.uv).x;
	gMetalness = boundMetalnessMap.Sample(samplerState, gInput.uv).x;
	gAmbientOcclusion = boundAmbientOcclusionMap.Sample(samplerState, gInput.uv).x;
	gEmissive = boundEmissiveMap.Sample(samplerState, gInput.uv).xyz;
	gMetalnessAlbedo = gAlbedo - (gAlbedo * gMetalness.xxx);
	gSubstance = (float3(0.04f, 0.04f, 0.04f) - (float3(0.04f, 0.04f, 0.04f) * gMetalness)) + gAlbedo * gMetalness;
    
    CalculateReflectionFresnel();

	CalculateFresnel();
	CalculateDistribution();
	CalculateVisibility();

	float3 directDiffuse = (0.f).xxx;
	float3 directSpecularity = (0.f).xxx;

    // foreach (light)
    {
        CalculateAmbientDiffuse();
        CalculateAmbientSpecularity();

        gLambert = saturate(dot(gObjectNormal, gToLight));

        directDiffuse += CalulateDirectDiffuse(directionLight[0].color.xyz);
        directSpecularity += CalulateDirectSpecularity(directionLight[0].color.xyz);
    }

	PixelOutput output;
    output.color.xyz = gAmbientDiffuse + gAmbientSpecularity + directDiffuse + directSpecularity + gEmissive;
	output.color.a = 1.0f;
	return output;
}
