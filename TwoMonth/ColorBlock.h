#pragma once
#include"2d/Sprite.h"
#include"3d/Object.h"
#include"base/Safe_delete.h"
#include"base/XMFLOATHelper.h"
#include"Table.h"
enum BlockColor
{
	Red = 1,
	Yellow,
	Blue,
	//�y��
	Foundation,
};
class ColorBlock
{
private:
	Object *object = nullptr;
public:
	ColorBlock();
	~ColorBlock();

	void Init(Object::ObjectData block, Object::ObjectData block2, Object::ObjectData block3,
		Object::ObjectData block4, Object::ObjectData block5, Object::ObjectData block6,
		Object::ObjectData block7, Object::ObjectData block8, Object::ObjectData block9, Object *object, int color, int redGraph, int yellowGraph, int blueGraph);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�e�N���X���擾
	void GetSpriteParent(Object::ObjectData *parent);
	//�����߂�����
	void PushBack(int isHit, const float blockSize);

	//�u���b�N����
	void SpeedUpdate();
	XMFLOAT3 GetPos();

	XMFLOAT3 GetoldPos();

	bool GetFlag();
	//�}�b�v�`�b�v���̏���ۑ��A��̏�ł̍��W������
	void Pos(int i, int j, int direction, const float blockSize);
	//���Ƀu���b�N���Ȃ��Ƃ��̍��W������
	void ShiftPos(int i, int j, int direction, const float blockSize);
	XMFLOAT2 Getmap();

	int GetStatus();

	int GetColor();

	int GetLevel();
	//���x���㏸
	void LevelUP(int i);

	bool GetDeleteFlag();
	//�t���O��TRUE�ɂ���
	void BreakFlagTRUE();
	//�G������
	void Sandwich();

	bool GetBreakFlag();
private:
	Object::ObjectData block[9];
	int redGraph = 0; 
	int yellowGraph = 0;
	int blueGraph = 0; 
	XMFLOAT3 pos{ 0.0f,400.0f,-51.0f };
	XMFLOAT3 oldPos{};
	XMFLOAT3 rotation{};
	bool Flag = true;//��ɏ���Ă邩�ǂ���
	int color = 0;//�F
	//�}�b�v�`�b�v�̈ʒu��ۑ�
	XMFLOAT2 map = { -1,-1 };
	int Status = 0;

	int Level = 1;

	//�u���b�N�����ރt���O
	bool  blockBreakFlag = false;
	bool  DeleteFlag = false;
	//�G�����ނ܂ł̎���
	int time = 20;
};