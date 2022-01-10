#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<vector>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
const int mapNum = 10;
enum BlockColor
{
	Red,
	Yellow,
	Blue,
};

class Block
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
public:
	Block();

	~Block();

	void Init(Input *input, Sprite *sprite);

	void Update();

	void Draw();

	//�u���b�N�ǉ�
	void AddBlock();
	//�u���b�N�ړ�
	void MoveBlock();
	//�u���b�N�Ƒ�̓����蔻��
	void ColBlock(Sprite::SpriteData *table,XMFLOAT2 tablePos,int direction);
	//�_���[�W
	void Damege();

	bool GetDameFlag();
private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData block;

	//�u���b�N�̃}�b�v�`�b�v
	int mapUP[10][mapNum];//��̏��
	int mapDown[10][mapNum];//���̏��
	int mapLeft[10][mapNum];//���̏��
	int mapRight[10][mapNum];//�E�̏��

	bool DamegeFlag = false;
};