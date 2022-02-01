#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include "3d/Object.h"
#include"Sound/Sound.h"
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
	Object *object = nullptr;
	Sound *sound = nullptr;
public:

	Table();
	~Table();

	void Init(Input *input, Sprite *sprite, Object *object, Sound *Sound);

	void MainInit();

	void Update();

	void Draw();

	XMFLOAT3 GetPos();
	//��̌���
	int GetStatus();
	//�X�v���C�g�f�[�^
	Object::ObjectData table;
	Sound::SoundData SoundTable;
	int graph = 0;
	//�V�F�C�N�X�V
	void ShakeUpdate();
	//�V�F�C�N�X�^�[�g/�V�F�C�N���ԁA�V�F�C�N�̋���
	void ShakeStart(float shakeTime, int shakeString);

	bool ShakeGet(bool shakeFlag);

	bool GetShakeFlag();

	int GetShakeTime();
private:
	XMFLOAT3 pos{ 0.0f,0.0f ,0.0f };//���W
	XMFLOAT3 rotation{};
	//300/210
	float width = 300.0f;

	float height = 300.0f;

	int Status = UP;

	//��]���Ă邩�ǂ���
	bool rotationFlag = false;
	float rotationMemory = 0;

	float shakeX = 0.0f, shakeY = 0.0f;	//�V�F�C�N�������̑傫��
	float shakeTime = 0.0f;				//�V�F�C�N����
	int  shakeString = 0;				//�V�F�C�N�̋���
	float shkeStringTime = 0.0f;		//����
	bool shakeFlag = false;				//�V�F�C�N�t���O
};