float RoughToSPow(float fRoughness)
{
	return (2.f / (fRoughness * fRoughness)) - 2.f;
}

static const float k0 = 0.00098f;
static const float k1 = 0.9921f;
static const float fMaxT = (exp2(-10.f / sqrt((2.f / (0.001f * 0.0014f)) - 2.f)) - 0.00098f) / 0.992; /* Don't know if it ends here */
float GetSpecPowToMip(float fSpecPow, int nMips)
{
	float fSmulMaxT = (exp2(-10.0f / sqrt(fSpecPow)) - k0) / k1;
	
	return float(nMips - 1 - 0) * (1.0 - clamp(fSmulMaxT / fMaxT, 0.0, 1.0));
}

/*static const float k0 = 0.00098, k1 = 0.9921;
static const float fakeLysMaxSpecularPower = (2.f / (0.001f * 0.001f)) - 2.f;
static const float g_fMaxT = (exp2(-10.0 / sqrt(fakeLysMaxSpecularPower)) - k0) / k1;
float GetSpecPowToMip(float fSpecPow, int nMips)
{
   // Default curve - Inverse of TB2 curve with adjusted constants
    float fSmulMaxT = (exp2(-10.0 / sqrt(fSpecPow)) - k0) / k1;
    return float(nMips - 1 - nMipOffset) * (1.0 - clamp(fSmulMaxT / g_fMaxT, 0.0, 1.0));
}*/
