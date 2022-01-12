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

	void ColorCheck();
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

	Sprite::SpriteData enemyGraph;///敵画像

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
	static const int enemy_Num = 5;//敵の数
	int enemyHP[enemy_Num] = { 3, 3, 3, 5, 5 };///体力
	bool enemyIsAlive[enemy_Num] = { 1, 1, 1, 1, 1 };///存在するか
	bool enemyIsAttack[enemy_Num] = { 0, 0, 0, 0, 0 };///攻撃しているか
	int enemyAttackDelay[enemy_Num] = { 5, 5, 5 ,5 ,5 };///攻撃するまでの時間
	int enemyColorTopL[enemy_Num] = { 1, 1, 1, 1, 1 };
	int enemyColorTopR[enemy_Num] = { 1, 1, 1, 1, 1 };
	int enemyColorBottomL[enemy_Num] = { 1, 1, 1, 1, 1 };
	int enemyColorBottomR[enemy_Num] = { 1, 1, 1, 1, 1 };

	int  enemyAttackCount = 0;///攻撃のカウント用

	//フェーズ
	int nowPhase = 0;
};