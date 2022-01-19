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
private://定義

	//音データ
	Sound::SoundData sound1;
	Sound::SoundData sound2;

	//スプライト画像
	Sprite::SpriteData spriteGraph;
	Sprite::SpriteData BGGraph;
	Sprite::SpriteData BG2Graph;

	Sprite::SpriteData enemyGraph;///敵画像
	Sprite::SpriteData phaseGraph;///敵画像
	Sprite::SpriteData titleGraph;///敵画像
	Sprite::SpriteData GameOverGraph;///敵画像



	Sprite::SpriteData UIGraph;//UI画像
	//オブジェクトの形
	Object::ObjectData Polygon;
	Object::ObjectData rayPolygon;
	Object::ObjectData BossPolygon;

	//オブジェクト画像
	int graph1;
	int graph2;
	int graph3;

	//座標
	XMFLOAT3 pPos1 = { 1.0f,1.0f,-100.0f };

	XMFLOAT3 pPos2 = { 2.0f,4.0f,5.0f };

	XMFLOAT3 angle = { 0.0f,0.0f,0.0f };

	//台クラス
	Table table;

	//ブロッククラス
	Block block;

	//プレイヤーステータス
	int playerHP = 3;///体力
	bool playerIsAlive = 1;///存在するか

	//敵ステータス
	static const int enemy_Num = 20;//敵の数
	int enemyHP[enemy_Num] =           { 3000, 3000, 3000, 5000, 5000, 5000, 7000, 7000, 7000, 9000, 9000, 9000, 3000, 5000, 5000, 3000, 3000, 3000, 5000, 5000 };///体力
	bool enemyIsAlive[enemy_Num] =     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };///存在するか
	bool enemyIsAttack[enemy_Num] =    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };///攻撃しているか
	int enemyAttackDelay[enemy_Num] =  { 5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 ,5, 5, 5 ,5 ,5 };///攻撃するまでの時間
	int enemyColorTopL[enemy_Num] =    { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorTopR[enemy_Num] =    { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1 ,3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomL[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColorBottomR[enemy_Num] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
	int enemyColor[enemy_Num] =        { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1 };
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

	float combo = 0;

	//エネミー攻撃オブジェクト関連
	XMFLOAT3 eAttackPos{ 0.0f,0.0f,0.0f };
	bool eAttackFlag = false;//アタック描画
	int  eAttackTime = 50;//アタックHP
	//いずれクラス内に入れるエネミー攻撃シェイク用変数
	float shakeX, shakeY;	//シェイクした分の大きさ
	float shakeTime;		//シェイク時間
	int  shakeString;		//シェイクの強さ
	float shkeStringTime;	//減衰
	bool shakeFlag;			//シェイクフラグ
	void ShakeUpdate();
	//シェイクスタート/シェイク時間、シェイクの強さ
	void ShakeStart(float shakeTime, int shakeString);

	//フェーズ
	int nowPhase = 0;
	int phaseDelay = 0;
	bool phaseFlag = 0;


	int scene = TitleInit;
};