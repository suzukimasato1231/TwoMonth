#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"


enum Direction
{
	UP,
	Down,
	Left,
	Right
};
class Table
{
private:
	Sprite *sprite = nullptr;
	Input *input = nullptr;
public:

	Table();
	~Table();

	void Init(Input *input, Sprite *sprite);

	void MainInit();

	void Update();

	void Draw();

	XMFLOAT2 GetPos();
	//��̌���
	int GetStatus();
	//�X�v���C�g�f�[�^
	Sprite::SpriteData table;

	//�V�F�C�N�X�V
	void ShakeUpdate();
	//�V�F�C�N�X�^�[�g/�V�F�C�N���ԁA�V�F�C�N�̋���
	void ShakeStart(float shakeTime, int shakeString);

	bool ShakeGet(bool shakeFlag);
private:
	XMFLOAT2 pos{ 950.0f,600.0f };//���W
	//300/210
	float width = 300.0f;

	float height = 300.0f;

	int Status = UP;

	//��]���Ă邩�ǂ���
	bool rotationFlag = false;
	float rotationMemory = 0;

	float shakeX, shakeY;	//�V�F�C�N�������̑傫��
	float shakeTime;		//�V�F�C�N����
	int  shakeString;		//�V�F�C�N�̋���
	float shkeStringTime;	//����
	bool shakeFlag;			//�V�F�C�N�t���O
};