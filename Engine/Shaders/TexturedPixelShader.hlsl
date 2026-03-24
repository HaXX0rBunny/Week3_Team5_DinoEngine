#include "ShaderCommon.hlsli"

Texture2D BaseTexture : register(t0);
SamplerState BaseSampler : register(s0);

cbuffer MaterialBuffer : register(b2)
{
	float4 BaseColor;
};

float4 main(VS_OUTPUT Input) : SV_TARGET
{
	float4 TexColor = BaseTexture.Sample(BaseSampler, Input.UV);
	return TexColor * BaseColor;
}
