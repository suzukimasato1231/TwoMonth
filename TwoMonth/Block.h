#pragma once
#include"2d/Sprite.h"
#include"3d/Object.h"
#include"Input/Input.h"
#include<vector>
#include<time.h>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
#include"Particle.h"
time_t time(time_t *);
const int mapNum = 20;

class Block
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
	Object *object = nullptr;
public:
	Block();

	~Block();

	//�v���C���[���u����b��
	time_t start_player, end_player;//���Ԍv��
	bool playerTimeFlag = false;//�v���C���[�^�[���t���O


	//������
	void Init(Input *input, Sprite *sprite, Object *object);
	//�Q�[�����[�v�̏�����
	void MainInit();
	//�X�V
	void Update(Object::ObjectData *table, int direction);
	//�`��
	void Draw();
	//UI�`��
	void DrawUI();
	//�u���b�N�Ƒ�̓����蔻��
	void ColBlock(Object::ObjectData *table, XMFLOAT3 tablePos, int direction);
	//�_���[�W
	void Damege();
	//�u���b�N�ƃ}�b�v�`�b�v������
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

	bool GetSandEndFlag();

	bool GetPutFlag();
	//�u���b�N������
	void SandwitchDelete();

	//�u���b�N�u�������̌x����`�悷��
	void WallningDraw();
	//�Q�[���I�[�o�[�܂ł̃J�E���g�̕`��
	void DrawGameOverCount();
	//���񂾎��̉��o�̍X�V
	void RockUpdate();
	//���񂾎��̉��o�̕`��
	void RockDraw();

	bool GetPlayerTimeFlag();

	int GetPTime();
private:
	//�u���b�N�ǉ�
	void AddBlock(int direction);
	//�u���b�N�ړ�
	void MoveBlock(Object::ObjectData *table, int direction);
	/// <summary>
	/// �u���b�N�����炷
	/// </summary>
	/// <param name="i">�}�b�v�`�b�v�̂�</param>
	/// <param name="j">�}�b�v�`�b�v�̂�</param>
	void BlockShift(int i, int j);

	//�n�[�h�h���b�v
	void HardDrop();
	//��]���̃u���b�N�̏���
	void BlockSetRot(Object::ObjectData *table, int direction);
	//�u���b�N����
	void BlockJoin();
	//�Q�[���I�[�o�[�܂ł̎��Ԃ��v��
	void CountGamaeOverTime();
	//�u���b�N�����ӂꂽ���ǂ�
	void Overflow();

	//���܂����}�b�v�`�b�v�̈ʒu���O�ɂ���
	void MapDelete();

	void PlayerTime();
private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData blocknext[9];
	Object::ObjectData block[9];
	//�摜
	int blueGraph = 0;
	int redGraph = 0;
	int yellowGraph = 0;

	//�u���b�N�̃}�b�v�`�b�v
	int mapUP[mapNum];//��̏��
	int mapDown[mapNum];//���̏��
	int mapLeft[mapNum];//���̏��
	int mapRight[mapNum];//�E�̏��

	int oldmapUP[mapNum];//��̏��
	int oldmapDown[mapNum];//���̏��
	int oldmapLeft[mapNum];//���̏��
	int oldmapRight[mapNum];//�E�̏��

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

	const int mapoverY = 8;				//������u���b�N�̍ő吔
	time_t start_time[4], end_time[4];//���Ԍv��
	bool blockOverFlag[4] = {};//�u���b�N���I�[�o�[�������ǂ���
	int gameOverCount[4] = { 0,0,0,0 };	//�Q�[���I�[�o�[�^�C���J�E���g
	bool gameOverFlag = false;//�Q�[���[�I�[�o�[
	const int gameOverTimeMax = 5;//�I�[�o�[�^�C���i�T���j

	Object::ObjectData warningNumber;//�u���b�N�u�������x������
	int warningNumberGraph[9];
	Object::ObjectData warningWall;		//�x���̐Ԃ��V�[�g
	int warningGraph = 0;//�Ԃ��g�摜
	Object::ObjectData outWarningWall;
	int outWarningGraph = 0;//�Ԃ��V�[�g�摜�O��
	int outWarningTime = 0;


	bool ShakeFlag = false;//�V�F�C�N�t���O

	//�u���b�N������p�[�e�B�N��
	vector<Particle *>rock;
	Object::ObjectData rockPolygon;
	int rockGraph;

	//�ݒu�t���O
	bool putFlag = false;
};