#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"


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
public:

	Table();
	~Table();

	void Init(Input *input, Sprite *sprite);

	void MainInit();

	void Update();

	void Draw();

	XMFLOAT2 GetPos();
	//台の向き
	int GetStatus();
	//スプライトデータ
	Sprite::SpriteData table;

	//シェイク更新
	void ShakeUpdate();
	//シェイクスタート/シェイク時間、シェイクの強さ
	void ShakeStart(float shakeTime, int shakeString);

	bool ShakeGet(bool shakeFlag);
private:
	XMFLOAT2 pos{ 950.0f,600.0f };//座標
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