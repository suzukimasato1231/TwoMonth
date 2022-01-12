#pragma once
#include"2d/Sprite.h"
#include"base/Safe_delete.h"
#include"base/XMFLOATHelper.h"
#include"Table.h"
enum BlockColor
{
	Red = 1,
	Yellow,
	Blue,
};
class ColorBlock
{
private:
	Sprite *sprite = nullptr;
public:
	ColorBlock();
	~ColorBlock();

	void Init(Sprite::SpriteData block, Sprite *sprite);
	//更新
	void Update();
	//描画
	void Draw();
	//親クラスを取得
	void GetSpriteParent(Sprite::SpriteData *parent);
	//押し戻し処理
	void PushBack(int isHit, const float blockSize);


	XMFLOAT2 GetPos();

	XMFLOAT2 GetoldPos();

	bool GetFlag();
	//マップチップ内の情報を保存、台の上での座標を入れる
	void Pos(int i, int j, int direction, const float blockSize);
	//下にブロックがないときの座標を入れる
	void ShiftPos(int i, int j, int direction, const float blockSize);
	XMFLOAT2 Getmap();

	int GetStatus();

	int GetColor();
private:
	Sprite::SpriteData block;
	XMFLOAT2 pos{ 900.0f,210.0f };
	XMFLOAT2 oldPos{};
	bool Flag = true;//台に乗ってるかどうか
	int color = 0;//色
	//マップチップの位置を保存
	XMFLOAT2 map = { -1,-1 };
	int Status = 0;
};