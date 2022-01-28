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
#include"Enemy.h"
#include"SceneChange.h"
#include"Tutorial.h"
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

	Sprite::SpriteData phaseGraph;///敵画像
	Sprite::SpriteData titleGraph;///敵画像
	Sprite::SpriteData GameOverGraph;///敵画像
	Sprite::SpriteData numGraph[10];///数字画像
	Sprite::SpriteData EnemyHpGraph;///数字画像

	Sprite::SpriteData UIGraph;//UI画像
	//オブジェクトの形
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

	//敵
	Enemy enemy;
	//シーンチェンジクラス
	SceneChange sceneChange;
	//チュートリアルクラス
	Tutorial tutorial;
	//プレイヤーステータス
	int playerHP = 3;///体力
	bool playerIsAlive = 1;///存在するか

	int scene = TitleInit;
	int turnNum = 0;
	int phaseNum = 0;			//フェーズ数１桁目
	bool phaseNum2Flag = false;	//２桁目に入ったか
	int phaseNum2 = 0;			//フェーズ数２桁目

	float hpRatio = 0;
};