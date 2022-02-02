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

	void DrawDamege();//ダメージ表現

	void PhaseUpdate(bool CheckFlag, bool DamegeFlag, int ComboCount, int colorNumUP, int colorNumDown, int colorNumLeft, int colorNumRight, int direction);
	//ダメージ計算
	void DamegeCal(bool DamegeFlag);
	//色情報初期化
	void ColorInformationInit();
	//フェーズフラグ取得
	bool GetphaseFlag();

	void betaDamageCheck(int ComboCount);

	void DamageCheck(int ComboCount, int direction);

	int GetEnemyColor(int parts);

	int GetDamegeValue(int i, int angle);

	int GetEnemyLastHP();

	int GetPhaseDelay();

	void FlagChenge();
	//アタックカウント取得
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
	Object::ObjectData enemyPolygon[6];///敵画像

	Object::ObjectData Polygon;

	Sprite::SpriteData damege;
	//敵ステータス
	static const int enemy_Num = 20;//敵の数
	float enemyHP[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///体力
	bool enemyIsAlive[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///存在するか
	bool enemyIsAttack[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///攻撃しているか
	int enemyAttackDelay[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///攻撃するまでの時間
	int enemyColorTop[enemy_Num] = { 1, 2, 3, 1, 3, 1, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorDown[enemy_Num] = { 1, 2, 3, 1, 3, 1, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorLeft[enemy_Num] = { 1, 2, 3, 3, 2, 2, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorRight[enemy_Num] = { 1, 2, 3, 3, 2, 2, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColor[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	//初期化用
	const float enemyHPKeep[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///体力
	const bool enemyIsAliveKeep[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///存在するか
	const bool enemyIsAttackKeep[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///攻撃しているか
	const int enemyAttackDelayKeep[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///攻撃するまでの時間
	const int enemyColorTopKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorDownKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorLeftKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorRightKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };

	int enemyAttackCount = 0;///攻撃のカウント用


		   //ブロック
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

	//フェーズ
	int nowPhase = 0;
	int phaseDelay = 0;
	bool phaseFlag = false;

	double HpBar = 0;

	//エネミー攻撃オブジェクト関連
	XMFLOAT3 eAttackPos{ 0.0f,0.0f,0.0f };
	bool eAttackFlag = false;//アタック描画
	int  eAttackTime = 50;//アタックタイム
	//いずれクラス内に入れるエネミー攻撃シェイク用変数
	XMFLOAT2 shakePos = {};
	float shakeTime;		//シェイク時間
	int  shakeString;		//シェイクの強さ
	float shkeStringTime;	//減衰
	bool shakeFlag;			//シェイクフラグ
	void ShakeUpdate();
	//シェイクスタート/シェイク時間、シェイクの強さ
	void ShakeStart(float shakeTime, int shakeString);

	bool enemyDameDirecting = false;
	int enemyDameTime = 0;//ダメージ食らったときの演出

	bool enemyDeadFlag = false;

	bool damegeHitFlag = false;//ダメージ表現用フラグ
	XMFLOAT4 damegeColor = { 1.0f,1.0f,1.0f,1.0f };
};