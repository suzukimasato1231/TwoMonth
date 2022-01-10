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

	void Update();

	void Draw();

	XMFLOAT2 GetPos();

	int GetStatus();

	Sprite::SpriteData table;
private:
	XMFLOAT2 pos{ 630.0f,420.0f };//ç¿ïW

	float width = 300.0f;

	float height = 300.0f;

	int Status = UP;
};