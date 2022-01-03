#pragma once
#include <DirectXMath.h>
#include <wrl.h>
using namespace DirectX;

extern const int window_width;
extern const int window_height;

class View
{
private:
	//ビュー変換行列
	XMMATRIX matView;
	//射影変換
	XMMATRIX matProjection;

	XMFLOAT3 eye = {}, target = {}, up = {};
public:
	View();

	~View();

	/// <summary>
	/// カメラ生成
	/// </summary>
	/// <returns></returns>
	static View *Create();

	//カメラ初期化/カメラ位置eye/カメラターゲットtarget /カメラの向きup
	void Initilize(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up);
	//カメラ位置セット/カメラ位置eye/カメラターゲットtarget /カメラの向きup
	void SetViewCamera(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up);

	/// <summary>
	/// カメラが追従する
	/// </summary>
	/// <param name="position">追従するオブジェクトの座標</param>
	/// <param name="up">カメラの向き</param>
	/// <param name="d">オブジェクトとカメラの距離</param>
	/// <param name="angleX">カメラの向きX</param>
	/// <param name="angleY">カメラの向きY</param>
	/// <returns></returns>
	void FollowView(XMFLOAT3 position, XMFLOAT3 d, float angleX = 0, float angleY = 0);

	//matViewを獲得
	XMMATRIX GetMatView();
	//projectionを獲得
	XMMATRIX GetProjection();

	XMFLOAT3 GetEye();
};