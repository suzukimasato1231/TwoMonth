#pragma once
#include<d3dcompiler.h>
#include<DirectXTex.h>
#include<d3dx12.h>
#include<wrl.h>
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class Pipeline
{
public:
	//構造体
	struct PipelineSet
	{
		//パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState>pipelinestate;
		//ルートシグネチャ
		ComPtr <ID3D12RootSignature>rootsignature;
	};
	//3Dオブジェクト
	static PipelineSet  Object3dCreateGraphicsPipeline(ID3D12Device *dev);
	//スプライト
	static PipelineSet  SpriteCreateGraphicsPipeline(ID3D12Device *dev);
	//OBJ読み込み
	static PipelineSet  OBJCreateGraphicsPipeline(ID3D12Device *dev);
};