
#include "BasicShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);//0番スロットに指定されたテクスチャ
SamplerState smp : register(s0);//０番スロットに指定されたサンプラー



float4 main(VSOutput input) : SV_TARGET
{

	float4 texcolor = float4(tex.Sample(smp,input.uv));

	float3 light = normalize(float3(-1,1,1));//　向きのライト
	float diffuse = saturate(dot(-light,input.normal));
	float brightness = diffuse + 0.3f;//光源のベクトルと法線ベクトルの内積
	return float4(texcolor.rgb * brightness,texcolor.a) * color;
	
}

