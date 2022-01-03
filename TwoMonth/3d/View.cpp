#include "View.h"

View::View()
{
	matView = XMMatrixIdentity();
	//�ˉe�ϊ�
	matProjection = XMMatrixIdentity();
}

View::~View()
{
}

View *View::Create()
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	View *view = new View();
	if (view == nullptr) {
		return nullptr;
	}

	// ������
	return view;
}

void View::Initilize(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up)
{
	//�ˉe�ϊ��p
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

	//�ˉe�ϊ��p
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 5100.0f
	);
}

void View::FollowView(XMFLOAT3 position, XMFLOAT3 d, float angleX, float angleY)
{
	target = position;//�����_���W
   //�J�����Ǐ]
   //1
	XMFLOAT3 V0 = d;
	//2
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleX));//Y��
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleY));//X��
	//3
	XMVECTOR v3 = { V0.x,V0.y,V0.z };
	XMVECTOR v = XMVector3TransformNormal(v3, rotM);

	//4
	XMFLOAT3 f3 = { v.m128_f32[0],v.m128_f32[1],v.m128_f32[2] };
	eye.x = target.x + f3.x, eye.y = target.y + f3.y, eye.z = target.z + f3.z;

	//5
	//�r���[�ϊ��s��
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
