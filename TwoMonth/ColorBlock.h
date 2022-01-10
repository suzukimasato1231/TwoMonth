#pragma once
#include"2d/Sprite.h"
#include"base/Safe_delete.h"
#include"base/XMFLOATHelper.h"
#include"Table.h"
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
	//���ړ�
	void LeftMove();
	//�E�ړ�
	void RightMove();
	//�e�N���X���擾
	void GetSpriteParent(Sprite::SpriteData *parent);
	//�����߂�����
	void PushBack(XMFLOAT2 mapChip, int isHit);

	
	XMFLOAT2 GetPos();

	XMFLOAT2 GetoldPos();

	bool GetFlag();
	//�}�b�v�`�b�v���̏���ۑ��A��̏�ł̍��W������
	void Pos(int i, int j,int direction);

	XMFLOAT2 Getmap();

	int GetStatus();
private:
	Sprite::SpriteData block;
	XMFLOAT2 pos{ 600.0f,0.0f };
	XMFLOAT2 oldPos{};
	bool Flag = true;
	//�}�b�v�`�b�v�̈ʒu��ۑ�
	XMFLOAT2 map = {-1,-1};
	int Status = 0;
};