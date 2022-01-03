#include "View.h"

View::View()
{
	matView = XMMatrixIdentity();
	//射影変換
	matProjection = XMMatrixIdentity();
}

View::~View()
{
}

View *View::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	View *view = new View();
	if (view == nullptr) {
		return nullptr;
	}

	// 初期化
	return view;
}

void View::Initilize(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up)
{
	//射影変換用
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 5100.0f
	);
	this->eye = eye, this->target = target, this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void View::SetViewCamera(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up)
{
	this->eye = eye, this->target = target, this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	//射影変換用
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 5100.0f
	);
}

void View::FollowView(XMFLOAT3 position, XMFLOAT3 d, float angleX, float angleY)
{
	target = position;//注視点座標
   //カメラ追従
   //1
	XMFLOAT3 V0 = d;
	//2
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleX));//Y軸
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleY));//X軸
	//3
	XMVECTOR v3 = { V0.x,V0.y,V0.z };
	XMVECTOR v = XMVector3TransformNormal(v3, rotM);

	//4
	XMFLOAT3 f3 = { v.m128_f32[0],v.m128_f32[1],v.m128_f32[2] };
	eye.x = target.x + f3.x, eye.y = target.y + f3.y, eye.z = target.z + f3.z;

	//5
	//ビュー変換行列
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

XMMATRIX View::GetMatView()
{
	return matView;
}

XMMATRIX View::GetProjection()
{
	return matProjection;
}

XMFLOAT3 View::GetEye()
{
	return eye;
}
