#pragma once
#include "base/_DirectX.h"
#include "base/Safe_delete.h"
#include "Input/Input.h"
#include"2d/DebugText.h"
#include "3d/Object.h"
#include"3d/ParticleManager.h"
#include"Collision/Collision.h"
#include"Sound/Sound.h"
#include"Table.h"
#include"Block.h"
extern const int window_width;
extern const int window_height;

enum Scene
{
	TitleInit,
	Title,
	MainInit,
	Main,
	GameOverInit,
	GameOver,
	GameClearInit,
	GameClear,
};

class GameSceneManager
{
private:
	Input *input = nullptr;
	_DirectX *directX = nullptr;
public:
	GameSceneManager();
	~GameSceneManager();

	void Initialize(Input *input, _DirectX *directX);

	void Init();

	void Update();

	void Draw(_DirectX directX);

	void ColorDamageCheck();

	void DamageCheck();


	float betaDamageValueCheck();
	void betaDamageCheck();
private:
	Object *object = nullptr;
	Sprite *sprite = nullptr;
	ParticleManager *particleMan = nullptr;
	View *view = nullptr;
	Light *light = nullptr;
	DebugText debugText;
	Sound *sound = nullptr;
private://��`

	//���f�[�^
	Sound::SoundData sound1;
	Sound::SoundData sound2;

	//�X�v���C�g�摜
	Sprite::SpriteData spriteGraph;
	Sprite::SpriteData BGGraph;
	Sprite::SpriteData BG2Graph;

	Sprite::SpriteData enemyGraph;///�G�摜
	Sprite::SpriteData phaseGraph;///�G�摜
	Sprite::SpriteData titleGraph;///�G�摜
	Sprite::SpriteData GameOverGraph;///�G�摜



	Sprite::SpriteData UIGraph;//UI�摜
	//�I�u�W�F�N�g�̌`
	Object::ObjectData Polygon;
	Object::ObjectData rayPolygon;
	Object::ObjectData BossPolygon;

	//�I�u�W�F�N�g�摜
	int graph1;
	int graph2;
	int graph3;

	//���W
	XMFLOAT3 pPos1 = { 1.0f,1.0f,-100.0f };

	XMFLOAT3 pPos2 = { 2.0f,4.0f,5.0f };

	XMFLOAT3 angle = { 0.0f,0.0f,0.0f };

	//��N���X
	Table table;

	//�u���b�N�N���X
	Block block;

	//�v���C���[�X�e�[�^�X
	int playerHP = 3;///�̗�
	bool playerIsAlive = 1;///���݂��邩

	//�G�X�e�[�^�X
	static const int enemy_Num = 20;//�G�̐�
	int enemyHP[enemy_Num] =           { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///�̗�
	bool enemyIsAlive[enemy_Num] =     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///���݂��邩
	bool enemyIsAttack[enemy_Num] =    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///�U�����Ă��邩
	int enemyAttackDelay[enemy_Num] =  { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///�U������܂ł̎���
	int enemyColorTopL[enemy_Num] =    { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorTopR[enemy_Num] =    { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomL[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomR[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColor[enemy_Num] =        { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	//�������p
	const int enemyHPKeep[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///�̗�
	const bool enemyIsAliveKeep[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///���݂��邩
	const bool enemyIsAttackKeep[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///�U�����Ă��邩
	const int enemyAttackDelayKeep[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///�U������܂ł̎���
	const int enemyColorTopLKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorTopRKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorBottomLKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorBottomRKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	
	int enemyAttackCount = 0;///�U���̃J�E���g�p

	   //�u���b�N
	int colorUp[100];
	int colorDown[100];
	int colorLeft[100];
	int colorRight[100];

	float damageValueUpL[100];
	float damageValueUpR[100];
	float damageValueDownL[100];
	float damageValueDownR[100];
	float damageValueLeftL[100];
	float damageValueLeftR[100];
	float damageValueRightL[100];
	float damageValueRightR[100];


	float damageUpValue[100];
	float damageDownValue[100];
	float damageLeftValue[100];
	float damageRightValue[100];
	
	float damageValue[100];

	float damage;

	float damagaHigh = 200;
	float damageNormal = 100;
	float damageLow = 50;

	float combo = 0;

	//�G�l�~�[�U���I�u�W�F�N�g�֘A
	XMFLOAT3 eAttackPos{ 0.0f,0.0f,0.0f };
	bool eAttackFlag = false;//�A�^�b�N�`��
	int  eAttackTime = 50;//�A�^�b�NHP
	//������N���X���ɓ����G�l�~�[�U���V�F�C�N�p�ϐ�
	float shakeX, shakeY;	//�V�F�C�N�������̑傫��
	float shakeTime;		//�V�F�C�N����
	int  shakeString;		//�V�F�C�N�̋���
	float shkeStringTime;	//����
	bool shakeFlag;			//�V�F�C�N�t���O
	void ShakeUpdate();
	//�V�F�C�N�X�^�[�g/�V�F�C�N���ԁA�V�F�C�N�̋���
	void ShakeStart(float shakeTime, int shakeString);

	//�t�F�[�Y
	int nowPhase = 0;
	int phaseDelay = 0;
	bool phaseFlag = 0;


	int scene = TitleInit;
};