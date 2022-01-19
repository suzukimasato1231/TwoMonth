#pragma once
#include"2d/Sprite.h"
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
	Sprite *sprite = nullptr;
public:
	ColorBlock();
	~ColorBlock();

	void Init(Sprite::SpriteData block, Sprite::SpriteData block2, Sprite::SpriteData block3,
		Sprite::SpriteData block4, Sprite::SpriteData block5, Sprite::SpriteData block6,
		Sprite::SpriteData block7, Sprite::SpriteData block8, Sprite::SpriteData block9, Sprite *sprite, int color);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�e�N���X���擾
	void GetSpriteParent(Sprite::SpriteData *parent);
	//�����߂�����
	void PushBack(int isHit, const float blockSize);


	XMFLOAT2 GetPos();

	XMFLOAT2 GetoldPos();

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
private:
	Sprite::SpriteData block[9];
	XMFLOAT2 pos{ 900.0f,100.0f };
	XMFLOAT2 oldPos{};
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