#pragma once
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
	//���݂̍��W���擾
	XMFLOAT3 GetPos();
	//�P�O�̍��W���擾
	XMFLOAT3 GetoldPos();
	//��ɏ���Ă��邩�̃t���O���擾
	bool GetMoveFlag();
	//�}�b�v�`�b�v���̏���ۑ��A��̏�ł̍��W������
	void Pos(int i, int j, int direction, const float blockSize);
	//���Ƀu���b�N���Ȃ��Ƃ��̍��W������
	void ShiftPos(int i, int j, int direction, const float blockSize);
	//�}�b�v�`�b�v�ʒu�擾
	XMFLOAT2 Getmap();
	//�㉺���E�̂ǂꂩ�擾
	int GetStatus();
	//�F���擾
	int GetColor();
	//�d�Ȃ��������擾
	int GetLevel();
	//���x���㏸
	void LevelUP(int i);
	//�����邩�ǂ����̃t���O���擾
	bool GetDeleteFlag();
	//�t���O��TRUE�ɂ���
	void BreakFlagTRUE();
	//�G������
	void Sandwich();
	//�u���b�N�����ރt���O���擾
	bool GetBreakFlag();
private:
	Object::ObjectData block[9];		//�u���b�N�̃I�u�W�F�N�g�f�[�^
	int redGraph = 0;					//�Ԃ̃u���b�N�̉摜�f�[�^�ʒu
	int yellowGraph = 0;				//���F�̃u���b�N�̉摜�f�[�^�ʒu
	int blueGraph = 0;					//�̃u���b�N�̉摜�f�[�^�ʒu
	XMFLOAT3 pos{ 0.0f,400.0f,-51.0f };	//���݂̍��W
	XMFLOAT3 oldPos{};					//1�O�̍��W
	XMFLOAT3 rotation{};				//��]�ʒu
	bool moveFlag = true;				//��ɏ���Ă邩�ǂ���
	int color = 0;						//�F
	XMFLOAT2 map = { -1,-1 };			//�}�b�v�`�b�v�̂ǂ̈ʒu��
	int Status = 0;						//�㉺���E�̂ǂ���
	int Level = 1;						//�d�Ȃ��Ă鐔

	bool  blockBreakFlag = false;		//�u���b�N�����ރt���O
	bool  DeleteFlag = false;			//�����邩�ǂ���
	int time = 20;						//�G�����ނ܂ł̎���
};