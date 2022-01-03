#pragma once
#include<Windows.h>
#include<wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "_Window.h."
extern const int window_width;
extern const int window_height;

class _DirectX
{
public:

	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
private://メンバ変数
	//ウィンドウ関連
	_Window *win;

	//DirectX3D関連
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList >cmdList;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue >cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap>rtvHeaps;
	//深度設定
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//フェンスの生成
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

private:
	//アダプタの列挙
	void Adapter();

	//コマンドリスト
	void CommandListInitilize();

	//スワップチェーン
	void Swapchain();
	//深度設定
	void DepthBuffer();
	
public://メンバ関数
	_DirectX();

	~_DirectX()
	{

	}
	//初期化
	void Initilize(_Window *win);

	//描画前処理
	void PreDraw();

	//描画後処理
	void ResourceBarrier();

	ID3D12Device* GetDevice();

	ID3D12GraphicsCommandList* GetCmandList();

	void ClearDepthBuffer();
	
};
