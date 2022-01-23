#pragma once
#include"ColorBlock.h"
#include "3d/Object.h"
class Enemy
{
public:
	Enemy();

	~Enemy();

private:
	Sprite *sprite = nullptr;
	Object *object = nullptr;
public:
	void Init(Sprite *sprite, Object *object);

	void MainInit();

	void Update(int &playerHP, bool DamegeFlag, bool ComboCout);

	void Draw();

	void AttackDraw();

	void PhaseUpdate(bool CheckFlag, bool DamegeFlag, int ComboCount, int colorNumUP, int colorNumDown, int colorNumLeft, int colorNumRight);
	//�_���[�W�v�Z
	void DamegeCal(bool DamegeFlag);
	//�_���[�W�`�F�b�N
	void ColorDamageCheck();
	//�F��񏉊���
	void ColorInformationInit();
	//�t�F�[�Y�t���O�擾
	bool GetphaseFlag();

	void betaDamageCheck(int ComboCount);

	int GetEnemyLastHP();

	int GetPhaseDelay();

	void FlagChenge();
	//�A�^�b�N�J�E���g�擾
	int GetAttackCount();

	int GetAttackDelay();

	int GetEnemyHP();

	int GetConstEnemyHP();

	int GetCombo();
	
	int GetHpBar();

	XMFLOAT2 GetShakePos();
private:
	Sprite::SpriteData enemyGraph[3];///�G�摜
	Object::ObjectData Polygon;
	//�G�X�e�[�^�X
	static const int enemy_Num = 20;//�G�̐�
	int enemyHP[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///�̗�
	bool enemyIsAlive[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///���݂��邩
	bool enemyIsAttack[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///�U�����Ă��邩
	int enemyAttackDelay[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///�U������܂ł̎���
	int enemyColorTopL[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorTopR[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomL[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomR[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColor[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
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

	int  combo = 0;

	//�t�F�[�Y
	int nowPhase = 0;
	int phaseDelay = 0;
	bool phaseFlag = 0;

	int HpBar = 0;

	//�G�l�~�[�U���I�u�W�F�N�g�֘A
	XMFLOAT3 eAttackPos{ 0.0f,0.0f,0.0f };
	bool eAttackFlag = false;//�A�^�b�N�`��
	int  eAttackTime = 50;//�A�^�b�NHP
	//������N���X���ɓ����G�l�~�[�U���V�F�C�N�p�ϐ�
	XMFLOAT2 shakePos = {};
	float shakeTime;		//�V�F�C�N����
	int  shakeString;		//�V�F�C�N�̋���
	float shkeStringTime;	//����
	bool shakeFlag;			//�V�F�C�N�t���O
	void ShakeUpdate();
	//�V�F�C�N�X�^�[�g/�V�F�C�N���ԁA�V�F�C�N�̋���
	void ShakeStart(float shakeTime, int shakeString);
};