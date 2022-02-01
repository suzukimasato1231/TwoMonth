#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include<forward_list>
#include"../base/XMFLOATHelper.h"
#include"View.h"
class ParticleManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // サブクラス

	struct VertexPos
	{
		XMFLOAT3 pos;
		float scale;//スケール
		XMFLOAT4 color;
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX matBillboard;//ビルボード行列
	};

	struct Particle
	{
		using XMFLOAT3 = DirectX::XMFLOAT3;

		//座標
		XMFLOAT3 position = {};
		//速度
		XMFLOAT3 velocity = {};
		//加速度
		XMFLOAT3 accel = {};
		//現在フレーム
		int frame = 0;
		//終了フレーム
		int num_frame = 0;
		//スケール
		float scale = 1.0f;
		//初期値
		float s_scale = 1.0f;
		//最終地
		float e_scale = 0.0f;

		//カラー
		XMFLOAT4 color = {};
		//初期値
		XMFLOAT4 s_color = {};
		//最終地
		XMFLOAT4 e_color = {};

	};
	//パーティクル配列
	std::forward_list<Particle>particles;

private: // 定数
	static const int vertexCount = 1024;//頂点数
public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	/// <returns>成否</returns>
	static bool StaticInitialize(ID3D12Device *device, ID3D12GraphicsCommandList *cmdList, View *view, int window_width, int window_height);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList *cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static ParticleManager *Create();


	/// <summary>
	/// パーティクルの追加
	/// </summary>
	/// <param name = "life">生存時間</param>
	/// <param name = "position">初期座標</param>
	/// <param name = "velocity">速度</param>
	/// <param name = "accel">加速度</param>
	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel,
		float start_scale, float end_scale, XMFLOAT4 start_color, XMFLOAT4 end_color);

	void ParticleAdd(XMFLOAT3 Pos);
	void EnemyRParticleAdd(XMFLOAT3 Pos);
	void EnemyGParticleAdd(XMFLOAT3 Pos);
	void EnemyBParticleAdd(XMFLOAT3 Pos);

	void PowerUpParticleAdd(XMFLOAT3 Pos, int combo,bool explosion);

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device *device;

	static View *view;

	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList *cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;

	static ComPtr<ID3D12Resource> constBuff; // 定数バッファ
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;

	// 頂点データ配列
	static VertexPos vertices[vertexCount];

	//ビルボード行列
	static XMMATRIX matBillboard;
	//Y軸回りビルボード行列
	static XMMATRIX matBillboardY;
private:// 静的メンバ関数
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	/// <returns></returns>
	static bool InitializeDescriptorHeap();

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static bool InitializeGraphicsPipeline();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
	static bool LoadTexture();

	/// <summary>
	/// モデル作成
	/// </summary>
	static void CreateModel();

public: // メンバ関数
	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private: // メンバ変数

	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//ローカルカラー
	XMFLOAT4 color = { 1,1,1,1 };
};

