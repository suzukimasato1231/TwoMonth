#pragma once
#include <DirectXMath.h>
#include <wrl.h>
using namespace DirectX;

extern const int window_width;
extern const int window_height;

class View
{
private:
	//�r���[�ϊ��s��
	XMMATRIX matView;
	//�ˉe�ϊ�
	XMMATRIX matProjection;

	XMFLOAT3 eye = {}, target = {}, up = {};
public:
	View();

	~View();

	/// <summary>
	/// �J��������
	/// </summary>
	/// <returns></returns>
	static View *Create();

	//�J����������/�J�����ʒueye/�J�����^�[�Q�b�gtarget /�J�����̌���up
	void Initilize(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up);
	//�J�����ʒu�Z�b�g/�J�����ʒueye/�J�����^�[�Q�b�gtarget /�J�����̌���up
	void SetViewCamera(XMFLOAT3 eye, XMFLOAT3 target, XMFLOAT3 up);

	/// <summary>
	/// �J�������Ǐ]����
	/// </summary>
	/// <param name="position">�Ǐ]����I�u�W�F�N�g�̍��W</param>
	/// <param name="up">�J�����̌���</param>
	/// <param name="d">�I�u�W�F�N�g�ƃJ�����̋���</param>
	/// <param name="angleX">�J�����̌���X</param>
	/// <param name="angleY">�J�����̌���Y</param>
	/// <returns></returns>
	void FollowView(XMFLOAT3 position, XMFLOAT3 d, float angleX = 0, float angleY = 0);

	//matView���l��
	XMMATRIX GetMatView();
	//projection���l��
	XMMATRIX GetProjection();

	XMFLOAT3 GetEye();
};