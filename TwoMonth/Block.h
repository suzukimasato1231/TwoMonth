#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<vector>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
const int mapNum = 20;

class Block
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
public:
	Block();

	~Block();

	void Init(Input *input, Sprite *sprite);

	void Update(Sprite::SpriteData *table, int direction);

	void Draw();

	//�u���b�N�Ƒ�̓����蔻��
	void ColBlock(Sprite::SpriteData *table,XMFLOAT2 tablePos,int direction);
	//�_���[�W
	void Damege();

	void DeleteBlock();

	bool GetDameFlag();

	bool GetAddFlag();
private:
	//�u���b�N�ǉ�
	void AddBlock();
	//�u���b�N�ړ�
	void MoveBlock(Sprite::SpriteData *table, int direction);
	/// <summary>
	/// �u���b�N�����炷
	/// </summary>
	/// <param name="i">�}�b�v�`�b�v�̂�</param>
	/// <param name="j">�}�b�v�`�b�v�̂�</param>
	void BlockShift(int i, int j);

	//�n�[�h�h���b�v
	void HardDrop(Sprite::SpriteData *table, int direction);
	//��]���̃u���b�N�̏���
	void BlockSetRot(Sprite::SpriteData *table, int direction);
private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData block;

	//�u���b�N�̃}�b�v�`�b�v
	int mapUP[mapNum];//��̏��
	int mapDown[mapNum];//���̏��
	int mapLeft[mapNum];//���̏��
	int mapRight[mapNum];//�E�̏��

	const float blockSize = 30.0f;
	//�}�b�v�`�b�v��X�̎c��
	const int blockX = 5;
	bool DamegeFlag = false;

	bool addFlag = false;
};