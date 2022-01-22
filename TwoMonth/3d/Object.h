#pragma once
#include<vector>
#include<string>
#include<d3dx12.h>
#include"../Pipeline/Pipeline.h"
#include"View.h"
#include<unordered_map>
#include"Light.h"
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3d12.lib")
const int constBufferNum = 256;
class Object
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static ID3D12Device *dev;					//デバイス
	static ID3D12GraphicsCommandList *cmdList;	//コマンドリスト
public://構造体
	//頂点データ構造体
	struct Vertex
	{
		XMFLOAT3 pos;//xyz座標
		XMFLOAT3 normal;//法線ベクトル
		XMFLOAT2 uv;//uv座標
	};

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMFLOAT4 color;
		XMMATRIX mat;//3D変換行列
	};
	//オブジェクトデータ構造体
	struct ObjectData
	{
		//頂点データ
		std::vector<Vertex *> vertices;
		//インデックスデータ
		std::vector<unsigned short *> indices;
		//頂点バッファの生成
		ComPtr<ID3D12Resource> vertBuff = nullptr;
		//インデックスバッファ
		ComPtr<ID3D12Resource> indexBuff = nullptr;
		//頂点バッファビューの作成
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		//インデックスバッファビューの作成
		D3D12_INDEX_BUFFER_VIEW ibView{};
		//ワールド行列
		XMMATRIX matWorld;
		//オブジェ読み込み用
		int OBJTexture = 0;
		//頂点法線スムージング用データ
		std::unordered_map<unsigned short, std::vector<unsigned short>>smoothData;
		ObjectData *parent = nullptr;
	};

	struct ConstBuffer
	{
		//GPUリソースの生成
		ComPtr<ID3D12Resource>constBuff = nullptr;
	};

	//OBJデータ関連
	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX viewproj;//ビュープロジェクション行列
		XMMATRIX world;//ワールド座標
		XMFLOAT3 cameraPos;//カメラ座標(ワールド座標)
	};
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//アンビエント係数
		float pad1;			//パディング
		XMFLOAT3 diffuse;	//ディフューズ係数
		float pad2;			//パディング
		XMFLOAT3 specular;	//スペキュラー係数
		float alpha;		//アルファ
	};
	//マテリアル
	struct Material
	{
		std::string name;			//マテリアル名
		XMFLOAT3 ambient;			//アンビエント影響度
		XMFLOAT3 diffuse;			//ディフューズ影響度
		XMFLOAT3 specular;			//スペキュラー影響度
		float alpha;				//アルファ
		std::string textureFilename;//テクスチャファイル名
		//コンストラクタ
		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
	//OBJ定数バッファ
	struct OBJData
	{
		ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
		ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ
	};
	//テクスチャデータ
	struct TextureData
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		ComPtr<ID3D12Resource> texbuff;
	};
public://パイプライン設定
	Pipeline::PipelineSet object3dPipelineSet;	//オブジェクト
	Pipeline::PipelineSet objPipelineSet;		//OBJ読み込み
public://変数	
	//テクスチャデータの作成
	std::vector <TextureData *>textureData;
	//OBJデータ
	std::vector<OBJData *> OBJdata;
	//定数バッファ用のデスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap >descHeap = { nullptr };
	//オブジェクトのコンストバッファ
	std::vector <ConstBuffer *>objectBuffer;
	//マテリアル
	Material material;
public:
	Object() {};
	~Object();

	//初期化
	void Init(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList, View *view, Light *light);

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object *Create();
public://カメラクラス
	static View *view;
	//ライト
	static Light *light;
public://図形モデル作成
	/// <summary>
	/// 三角錐
	/// </summary>
	/// <param name="width">横の長さ</param>
	/// <param name="height">縦の長さ</param>
	/// <returns></returns>
	ObjectData CreateTriangularPyramid(const float width, const float height);
	/// <summary>
	/// 短形
	/// </summary>
	/// <param name="width">横の長さ</param>
	/// <param name="height">縦の長さ</param>
	/// <returns></returns>
	ObjectData CreateRect(const float width, const float height);
	/// <summary>
	/// 円
	/// </summary>
	/// <param name="r">半径</param>
	/// <param name="num">分割数</param>
	/// <returns></returns>
	ObjectData CreateCircle(const float r, const int num);
	/// <summary>
	/// 立方体
	/// </summary>
	/// <param name="width">横の長さ</param>
	/// <param name="height">縦の長さ</param>
	/// <param name="depth">深さ</param>
	/// <returns></returns>
	ObjectData CreateSquare(const float width, const float height, const float depth);
	/// <summary>
	/// 円柱
	/// </summary>
	/// <param name="division">分割数</param>
	/// <param name="prizmHeight">高さ</param>
	/// <param name="radius">底面の半径</param>
	/// <returns></returns>
	ObjectData CreateCylinder(int division, int prizmHeight, int radius);
	/// <summary>
	/// OBJオブジェクト作成
	/// </summary>
	/// <param name="filename">filename</param>
	/// <param name="smoothing"></param>
	/// <returns></returns>
	ObjectData CreateOBJ(const std::string filename, bool smoothing = false);
public://オブジェクト関連
	//モデル作成
	void CreateModel(ObjectData &polygon);
	// テクスチャ読み込み
	int LoadTexture(const wchar_t *filename);
	//定数バッファ設定
	void ConstantBuffer();
	//オブジェクトのデータ更新
	void MatWord(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);
	//オブジェクト描画前
	void PreDraw();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="polygon">オブジェクトデータ </param>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="matRot">回転</param>
	/// <param name="color">色</param>
	/// <param name="graph">画像データ</param>
	void Draw(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3  matRot, XMFLOAT4 color, int graph = -1);
public://OBJ関連
	int OBJLoadTexture(const std::string &directoryPath, const std::string &filename);
	//マテリアル読み込み
	int LoadMaterial(const std::string &directoryPath, const std::string &filename);
	/// <summary>
	/// エッジ平滑化データの追加
	/// </summary>
	/// <param name="indexPosition">座標インデックス</param>
	/// <param name="indexVertex">頂点インデックス</param>
	void AddSmoothData(ObjectData &polygon, unsigned short indexPosition, unsigned short indexVertex);

	///<summary>
	///平滑化された頂点法線の計算
	/// </summary>
	void CalculateSmoothedVertexNormals(ObjectData &polygon);

	/// <summary>
	/// 頂点データの数を取得
	/// </summary>
	/// <returns>頂点データの数</returns>
	inline size_t GetVertexCount(ObjectData &polygon);
	//モデル作成
	void OBJCreateModel(ObjectData &polygon);
	//定数バッファ設定
	void OBJConstantBuffer();
	/// <summary>
	/// オブジェクトのデータ更新
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="matRot">回転</param>
	/// <param name="color">色</param>
	void OBJMatWord(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);
	/// <summary>
	/// OBJ描画
	/// </summary>
	/// <param name="polygon">オブジェクトデータ</param>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="matRot">回転</param>
	/// <param name="color">色</param>
	void OBJDraw(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color = { 1,1,1,1 });
public:
	size_t OBJNum = 0;//OBJ読み込みの数
	size_t objNum = 0;//オブジェクトの数
	size_t texNum = 0;//テクスチャの数
};