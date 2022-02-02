#pragma once
#include"ColorBlock.h"
#include "3d/Object.h"
#include"Sound/Sound.h"
class Enemy
{
public:
	Enemy();

	~Enemy();

private:
	Sprite *sprite = nullptr;
	Object *object = nullptr;
	Sound *sound = nullptr;
public:
	void Init(Sprite *sprite, Object *object, Sound *sound);

	void MainInit();

	void Update(int &playerHP, bool DamegeFlag, bool ComboCout, int pTime, bool tutorialFlag);

	void Draw();

	void AttackDraw();

	void DrawDamege();//�_���[�W�\��

	void PhaseUpdate(bool CheckFlag, bool DamegeFlag, int ComboCount, int colorNumUP, int colorNumDown, int colorNumLeft, int colorNumRight, int direction);
	//�_���[�W�v�Z
	void DamegeCal(bool DamegeFlag);
	//�F��񏉊���
	void ColorInformationInit();
	//�t�F�[�Y�t���O�擾
	bool GetphaseFlag();

	void betaDamageCheck(int ComboCount);

	void DamageCheck(int ComboCount, int direction);

	int GetEnemyColor(int parts);

	int GetDamegeValue(int i, int angle);

	int GetEnemyLastHP();

	int GetPhaseDelay();

	void FlagChenge();
	//�A�^�b�N�J�E���g�擾
	int GetAttackCount();

	int GetAttackDelay();

	float GetEnemyHP();

	float GetConstEnemyHP();

	bool GetEnemyDeadFlag();

	int GetCombo();

	double GetHpBar();

	XMFLOAT2 GetShakePos();

	bool GeteAttackFlag();

	void AttackInit();

	Sound::SoundData Sounddamege;
private:
	Object::ObjectData enemyPolygon[6];///�G�摜

	Object::ObjectData Polygon;

	Sprite::SpriteData damege;
	//�G�X�e�[�^�X
	static const int enemy_Num = 20;//�G�̐�
	float enemyHP[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///�̗�
	bool enemyIsAlive[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///���݂��邩
	bool enemyIsAttack[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///�U�����Ă��邩
	int enemyAttackDelay[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///�U������܂ł̎���
	int enemyColorTop[enemy_Num] = { 1, 2, 3, 1, 3, 1, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorDown[enemy_Num] = { 1, 2, 3, 1, 3, 1, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorLeft[enemy_Num] = { 1, 2, 3, 3, 2, 2, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorRight[enemy_Num] = { 1, 2, 3, 3, 2, 2, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColor[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	//�������p
	const float enemyHPKeep[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///�̗�
	const bool enemyIsAliveKeep[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///���݂��邩
	const bool enemyIsAttackKeep[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///�U�����Ă��邩
	const int enemyAttackDelayKeep[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///�U������܂ł̎���
	const int enemyColorTopKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorDownKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorLeftKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorRightKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };

	int enemyAttackCount = 0;///�U���̃J�E���g�p


		   //�u���b�N
	int colorUp[100];
	int colorDown[100];
	int colorLeft[100];
	int colorRight[100];

	float damageValueUp[100];
	float damageValueDown[100];
	float damageValueLeft[100];
	float damageValueRight[100];

	float damageUpValue[100];
	float damageDownValue[100];
	float damageLeftValue[100];
	float damageRightValue[100];

	float damageValue[100];

	float damage;

	float damagaHigh = 200;
	float damageNormal = 100;
	float damageLow = 50;

	int  combo = 0;

	//�t�F�[�Y
	int nowPhase = 0;
	int phaseDelay = 0;
	bool phaseFlag = false;

	double HpBar = 0;

	//�G�l�~�[�U���I�u�W�F�N�g�֘A
	XMFLOAT3 eAttackPos{ 0.0f,0.0f,0.0f };
	bool eAttackFlag = false;//�A�^�b�N�`��
	int  eAttackTime = 50;//�A�^�b�N�^�C��
	//������N���X���ɓ����G�l�~�[�U���V�F�C�N�p�ϐ�
	XMFLOAT2 shakePos = {};
	float shakeTime;		//�V�F�C�N����
	int  shakeString;		//�V�F�C�N�̋���
	float shkeStringTime;	//����
	bool shakeFlag;			//�V�F�C�N�t���O
	void ShakeUpdate();
	//�V�F�C�N�X�^�[�g/�V�F�C�N���ԁA�V�F�C�N�̋���
	void ShakeStart(float shakeTime, int shakeString);

	bool enemyDameDirecting = false;
	int enemyDameTime = 0;//�_���[�W�H������Ƃ��̉��o

	bool enemyDeadFlag = false;

	bool damegeHitFlag = false;//�_���[�W�\���p�t���O
	XMFLOAT4 damegeColor = { 1.0f,1.0f,1.0f,1.0f };
};