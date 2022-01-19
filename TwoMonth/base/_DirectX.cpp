#include "_DirectX.h"
#include <cassert>

_DirectX::_DirectX()
{

}
void _DirectX::Initilize(_Window *win)
{
	HRESULT result;
	assert(win);

	this->win = win;

#ifdef _DEBUG
	//デバックレイヤーをオン
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif
	//アダプタの列挙
	Adapter();

	//コマンドリスト
	CommandListInitilize();


	//深度設定
	DepthBuffer();

	//スワップチェーン
	Swapchain();

	//フェンスの生成
	result = dev->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

void _DirectX::Adapter()
{
	HRESULT result;
	//DXGIファクトリーの生成
	result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

	//アダプターの列挙用
	std::vector<ComPtr<IDXGIAdapter1>>adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter1>tmpAdapter = nullptr;
	//対応レベルの配列
	D3D_FEATURE_LEVEL levels[]
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	D3D_FEATURE_LEVEL featureLevel;
	for (int i = 0; i < _countof(levels); i++)
	{
		//採用したアダプターでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&dev));
		if (result == S_OK)
		{
			//デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}

	//ここに特定の名前を持つアダプターオブジェクトが入る
	for (int i = 0;
		dxgiFactory->EnumAdapters1(i, &tmpAdapter) !=
		DXGI_ERROR_NOT_FOUND;
		i++)
	{
		adapters.push_back(tmpAdapter);//動的配列に追加する
	}

	for (int i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC1 adesc;
		adapters[i]->GetDesc1(&adesc);//アダプターの情報を取得
		//ソフトウェアデバイスを回避
		if (adesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}
		std::wstring strDesc = adesc.Description;//アダプター名
		//Intel UHD Graphics（オンボードグラフィック）を回避
		if (strDesc.find(L"Intel") == std::wstring::npos)
		{
			tmpAdapter = adapters[i];//採用
			break;
		}
	}
}

void _DirectX::CommandListInitilize()
{
	HRESULT result;
	//コマンドアロケータを生成
	result = dev->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator));

	//コマンドリストを生成
	result = dev->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator.Get(), nullptr,
		IID_PPV_ARGS(&cmdList));

	//標準設定でコマンドキューを生成
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	//標準設定でコマンドキューを生成
	dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));
}

void _DirectX::Swapchain()
{
	HRESULT result;
	//各種設定をしてスワップチェーンを生成
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
	//各種設定をしてスワップチェーンを生成
	swapchainDesc.Width = window_width;
	swapchainDesc.Height = window_height;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//色情報を書式
	swapchainDesc.SampleDesc.Count = 1;//マルチサンプルにしない
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//バックバッファー用
	swapchainDesc.BufferCount = 2;//バッファ数を２つに設定
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//フリップ後は破棄
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGISwapChain1>swapchain1;

	dxgiFactory->CreateSwapChainForHwnd(
		cmdQueue.Get(),
		win->GetHwnd(),
		&swapchainDesc,
		nullptr,
		nullptr,
		&swapchain1);

	swapchain1.As(&swapchain);

	//各種設定をしてデスクリプタヒープを生成
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビュー
	heapDesc.NumDescriptors = 2;//裏表の２つ

	dev->CreateDescriptorHeap(&heapDesc,
		IID_PPV_ARGS(&rtvHeaps));

	//裏表の2つ分について
	backBuffers.resize(swapchainDesc.BufferCount);
	for (int i = 0; i < 2; i++)
	{
		//スワップチェーンからバッファを取得
		result = swapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));
		//レンダーターゲットビューの生成
		dev->CreateRenderTargetView(
			backBuffers[i].Get(),
			nullptr,
			CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeaps->GetCPUDescriptorHandleForHeapStart(),//ヒープの先頭アドレス
				i,//デスクリプタ番号
				dev->GetDescriptorHandleIncrementSize(heapDesc.Type)
			));
	}
}

void _DirectX::DepthBuffer()
{
	HRESULT result;
#pragma region	//深度設定
	//深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT,
		window_width,
		window_height,
		1, 0,
		1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	//深度バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,//深度値書き込みに使用
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
		IID_PPV_ARGS(&depthBuffer));


	//深度ビュー用デスクリプタヒープの作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;//深度ビューは１つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//デブスステンシルビュー

	result = dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	//深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dev->CreateDepthStencilView(
		depthBuffer.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart());

}


void _DirectX::PreDraw()
{
	//バックバッファの番号を取得（２つなので０番か１番）
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
#pragma region 1.リソースバリアで書き込み可能に変更
	//表示状態から描画状態に変更
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

#pragma region 2.描画先指定
	//レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeaps->GetCPUDescriptorHandleForHeapStart(),//ヒープの先頭アドレス
		bbIndex,//デスクリプタ番号
		dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)
	);

	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);


#pragma region	//3.画面クリア            R     G     B      A
	float clearColor[] = { 0.243f,0.545f,0.749f,0.0f };//青っぽい色

	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

#pragma region 4.描画コマンドはここから
	//ビューポートの設定コマンド
	cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, window_width, window_height));
	//シザー短形の設定コマンド
	cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, window_width, window_height));
}

//リソースバリアを戻す
void _DirectX::ResourceBarrier()
{
	//描画状態から表示状態に変更
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	//命令のクローズ
	cmdList->Close();
	//コマンドリストの実行
	ID3D12CommandList *cmdLists[] = { cmdList.Get() };//コマンドリストの配列
	cmdQueue->ExecuteCommandLists(1, cmdLists);

	
	//コマンドリストの実行完了を待つ
	cmdQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	cmdAllocator->Reset();//キューをクリア
	cmdList->Reset(cmdAllocator.Get(), nullptr);//再びコマンドリストを貯める準備

	//バッファをフリップ(裏表の入替え)
	swapchain->Present(1, 0);
}

ID3D12Device *_DirectX::GetDevice()
{
	return dev.Get();
}

ID3D12GraphicsCommandList *_DirectX::GetCmandList()
{
	return cmdList.Get();
}

void _DirectX::ClearDepthBuffer()
{
	// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvHeap->GetCPUDescriptorHandleForHeapStart());
	// 深度バッファのクリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}



