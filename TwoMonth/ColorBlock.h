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
};
class ColorBlock
{
private:
	Sprite *sprite = nullptr;
public:
	ColorBlock();
	~ColorBlock();

	void Init(Sprite::SpriteData block, Sprite *sprite);
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
private:
	Sprite::SpriteData block;
	XMFLOAT2 pos{ 900.0f,210.0f };
	XMFLOAT2 oldPos{};
	bool Flag = true;//��ɏ���Ă邩�ǂ���
	int color = 0;//�F
	//�}�b�v�`�b�v�̈ʒu��ۑ�
	XMFLOAT2 map = { -1,-1 };
	int Status = 0;
};