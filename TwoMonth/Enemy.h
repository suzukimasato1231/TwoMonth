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
	//ダメージ計算
	void DamegeCal(bool DamegeFlag);
	//ダメージチェック
	void ColorDamageCheck();
	//色情報初期化
	void ColorInformationInit();
	//フェーズフラグ取得
	bool GetphaseFlag();

	void betaDamageCheck(int ComboCount);

	int GetEnemyLastHP();

	int GetPhaseDelay();

	void FlagChenge();
	//アタックカウント取得
	int GetAttackCount();

	int GetAttackDelay();

	int GetEnemyHP();

	int GetConstEnemyHP();

	int GetCombo();
	
	int GetHpBar();

	XMFLOAT2 GetShakePos();
private:
	Sprite::SpriteData enemyGraph[3];///敵画像
	Object::ObjectData Polygon;
	//敵ステータス
	static const int enemy_Num = 20;//敵の数
	int enemyHP[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///体力
	bool enemyIsAlive[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///存在するか
	bool enemyIsAttack[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///攻撃しているか
	int enemyAttackDelay[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///攻撃するまでの時間
	int enemyColorTopL[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorTopR[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomL[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomR[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColor[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	//初期化用
	const int enemyHPKeep[enemy_Num] = { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///体力
	const bool enemyIsAliveKeep[enemy_Num] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///存在するか
	const bool enemyIsAttackKeep[enemy_Num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///攻撃しているか
	const int enemyAttackDelayKeep[enemy_Num] = { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///攻撃するまでの時間
	const int enemyColorTopLKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorTopRKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorBottomLKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorBottomRKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	const int enemyColorKeep[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };

	int enemyAttackCount = 0;///攻撃のカウント用


		   //ブロック
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

	//フェーズ
	int nowPhase = 0;
	int phaseDelay = 0;
	bool phaseFlag = 0;

	int HpBar = 0;

	//エネミー攻撃オブジェクト関連
	XMFLOAT3 eAttackPos{ 0.0f,0.0f,0.0f };
	bool eAttackFlag = false;//アタック描画
	int  eAttackTime = 50;//アタックHP
	//いずれクラス内に入れるエネミー攻撃シェイク用変数
	XMFLOAT2 shakePos = {};
	float shakeTime;		//シェイク時間
	int  shakeString;		//シェイクの強さ
	float shkeStringTime;	//減衰
	bool shakeFlag;			//シェイクフラグ
	void ShakeUpdate();
	//シェイクスタート/シェイク時間、シェイクの強さ
	void ShakeStart(float shakeTime, int shakeString);
};