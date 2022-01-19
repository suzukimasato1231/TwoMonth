#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
/// <summary>
/// ライト
/// </summary>
class Light
{
private://エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBuffData
	{
		XMVECTOR lightv;	//ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor;//ライトの色
	};
private://静的メンバ変数
	//デバイス
	static ID3D12Device *device;
public://静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device *device);
private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuff;
	//ライト光線方向(単位ベクトル)
	XMVECTOR lightdir = { 0,0,1,0 };
	//ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティーフラグ
	bool dirty = false;
	
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuff();
	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightdir">ライト方向</param>
	void SetLightDir(const XMVECTOR &lightdir);

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightdir">ライト方向</param>
	void SetLightColor(const XMFLOAT3 &lightcolor);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList *cmdList, UINT rootParameterIndex);

	/// <summary>
	///インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static Light *Create();
};