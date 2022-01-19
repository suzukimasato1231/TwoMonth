#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<vector>
#include<time.h>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
time_t time(time_t *);
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

	void MainInit();

	void Update(Sprite::SpriteData *table, int direction);

	void Draw();

	//�u���b�N�Ƒ�̓����蔻��
	void ColBlock(Sprite::SpriteData *table,XMFLOAT2 tablePos,int direction);
	//�_���[�W
	void Damege();

	void DeleteBlock();

	bool GetDameFlag();

	bool GetCheckFlag();

	bool GetAddFlag();

	int GetSandDelay();

	int GetComboCount();

	int GetColorNumUp();
	int GetColorNumDown();
	int GetColorNumLeft();
	int GetColorNumRight();

	void SetSandDelay(int count);

	int GetGameOverCount(int i);

	bool GetGameOverFlag();

	bool GetShakeFlag();
private:
	//�u���b�N�ǉ�
	void AddBlock(int direction);
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
	//���x���ɍ��킹�ă}�b�v�`�b�v������
	void LevelDelete(int direction, int blockNum, int mapY);
	//�u���b�N����
	void BlockJoin();
	//�Q�[���I�[�o�[�܂ł̎��Ԃ��v��
	void CountGamaeOverTime();
	//�u���b�N�����ӂꂽ���ǂ�
	void Overflow();
private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData block[9];
	Sprite::SpriteData nextBlock;
	//�u���b�N�̃}�b�v�`�b�v
	int mapUP[mapNum];//��̏��
	int mapDown[mapNum];//���̏��
	int mapLeft[mapNum];//���̏��
	int mapRight[mapNum];//�E�̏��

	const float blockSize = 30.0f;
	//�}�b�v�`�b�v��X�̎c��
	const int blockX = 5;
	//�F�̃f�[�^�ێ�
	int memoryColor = 1;

	bool DamegeFlag = false;

	bool addFlag = false;

	int sandDelay = 0;
	bool sandFlag = 0;

	int comboCount = 0;

	bool checkFlag = 0;
	int checkColorUp = 0;
	int checkColorDown = 0;
	int checkColorLeft = 0;
	int checkColorRight = 0;

	time_t start_time[4], end_time[4];//���Ԍv��
	bool blockOverFlag[4] = {};//�u���b�N���I�[�o�[�������ǂ���
	bool gameOverFlag = false;//�Q�[���[�I�[�o�[
	const int gameOverTimeMax = 5;//�I�[�o�[�^�C���i�T���j
	int gameOverCount[4] = { 0,0,0,0 };	//�Q�[���I�[�o�[�^�C���J�E���g

	bool ShakeFlag = false;//�V�F�C�N�t���O
};