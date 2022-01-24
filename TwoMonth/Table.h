#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include "3d/Object.h"

enum Direction
{
	UP,
	Down,
	Left,
	Right
};
class Table
{
private:
	Sprite *sprite = nullptr;
	Input *input = nullptr;
	Object *object = nullptr;
public:

	Table();
	~Table();

	void Init(Input *input, Sprite *sprite, Object *object);

	void MainInit();

	void Update();

	void Draw();

	XMFLOAT3 GetPos();
	//台の向き
	int GetStatus();
	//スプライトデータ
	Object::ObjectData table;
	int graph = 0;
	//シェイク更新
	void ShakeUpdate();
	//シェイクスタート/シェイク時間、シェイクの強さ
	void ShakeStart(float shakeTime, int shakeString);

	bool ShakeGet(bool shakeFlag);

	bool GetShakeFlag();

	int GetShakeTime();
private:
	XMFLOAT3 pos{ 0.0f,0.0f ,0.0f };//座標
	XMFLOAT3 rotation{};
	//300/210
	float width = 300.0f;

	float height = 300.0f;

	int Status = UP;

	//回転してるかどうか
	bool rotationFlag = false;
	float rotationMemory = 0;

	float shakeX, shakeY;	//シェイクした分の大きさ
	float shakeTime;		//シェイク時間
	int  shakeString;		//シェイクの強さ
	float shkeStringTime;	//減衰
	bool shakeFlag;			//シェイクフラグ
};