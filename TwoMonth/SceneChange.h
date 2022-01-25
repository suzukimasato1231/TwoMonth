#pragma once
#pragma once
#include <DirectXMath.h>
#include"2d/Sprite.h"
#include"base/XMFLOATHelper.h"
extern const int window_width;
extern const int window_height;
class SceneChange
{
	using XMFLOAT4 = DirectX::XMFLOAT4;
private:
	Sprite *sprite = nullptr;
public://�V�[���`�F���W
	void Init(Sprite *sprite);
	//�F�擾
	XMFLOAT4 GetColor();
	//�V�[���`�F���W��
	bool GetChangeFlag();
	//�V�[���`�F���W�O���I��������
	bool Change();
	//�V�[���`�F���W���o�X�^�[�g
	void Start();
	//�V�[���`�F���W�X�V
	void Update();
	//�`��
	void Draw();
private:
	Sprite::SpriteData SceneGraph;
	bool sceneChangeFlag;//�Ó]���Ă��邩
	bool firstHalfFlag;//���o�̑O�����ǂ���
	XMFLOAT4 changeColor;
private://�t�F�[�Y�N���A
	Sprite::SpriteData phaseClearGraph;
	XMFLOAT3 phaseStart;				//�X�^�[�g�n�_
	XMFLOAT3 phaseEnd;				//�G���h�n�_
	float phaseEasingTime;
	float phaseMaxTime;				//�S�̎���[s]
	float phaseTimeRate;			//�����@���Ԃ��i�񂾂�(��)
	bool phaseFlag = true;
public:
	//�X�R�A�C�[�W���O/�X�^�[�g�ʒu�A�I���ʒu�A�i�ގ���
	void phaseEasingStart(XMFLOAT3 start, XMFLOAT3 end, float Time);
	//�X�R�A�C�[�W���O�X�V
	XMFLOAT3 phaseEasing();

	void DrawPhase();

	void ChangePhaseFlag();
private://�Q�[���I�[�o�[
	Sprite::SpriteData gameOverGraph;
	bool gameoverFlag = true;
public:
	//�X�R�A�C�[�W���O/�X�^�[�g�ʒu�A�I���ʒu�A�i�ގ���
	void gameoverasingStart(XMFLOAT3 start, XMFLOAT3 end, float Time);
	//�X�R�A�C�[�W���O�X�V
	XMFLOAT3 gameoverEasing();

	void ChangePhasegameoverFlag();

	void DrawGameOver();
};


//��Ԋ֐�
//���`���
const XMFLOAT3 lerp(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);
const XMFLOAT3 easeIn(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);
const XMFLOAT3 easeOut(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);
const XMFLOAT3 easeInOut(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);