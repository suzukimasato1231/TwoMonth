#pragma once
#include "base/_DirectX.h"
#include "base/Safe_delete.h"
#include "Input/Input.h"
#include"2d/DebugText.h"
#include "3d/Object.h"
#include"3d/ParticleManager.h"
#include"Collision/Collision.h"
#include"Sound/Sound.h"
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
};