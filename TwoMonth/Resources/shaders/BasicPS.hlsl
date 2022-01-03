
#include "BasicShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);//0�ԃX���b�g�Ɏw�肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//�O�ԃX���b�g�Ɏw�肳�ꂽ�T���v���[



float4 main(VSOutput input) : SV_TARGET
{

	float4 texcolor = float4(tex.Sample(smp,input.uv));

	float3 light = normalize(float3(-1,1,1));//�@�����̃��C�g
	float diffuse = saturate(dot(-light,input.normal));
	float brightness = diffuse + 0.3f;//�����̃x�N�g���Ɩ@���x�N�g���̓���
	return float4(texcolor.rgb * brightness,texcolor.a) * color;
	
}

