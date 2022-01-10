#pragma once
#include"2d/Sprite.h"
#include"base/Safe_delete.h"
#include"base/XMFLOATHelper.h"
#include"Table.h"
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
	//左移動
	void LeftMove();
	//右移動
	void RightMove();
	//親クラスを取得
	void GetSpriteParent(Sprite::SpriteData *parent);
	//押し戻し処理
	void PushBack(XMFLOAT2 mapChip, int isHit);

	
	XMFLOAT2 GetPos();

	XMFLOAT2 GetoldPos();

	bool GetFlag();
	//マップチップ内の情報を保存、台の上での座標を入れる
	void Pos(int i, int j,int direction);

	XMFLOAT2 Getmap();

	int GetStatus();
private:
	Sprite::SpriteData block;
	XMFLOAT2 pos{ 600.0f,0.0f };
	XMFLOAT2 oldPos{};
	bool Flag = true;
	//マップチップの位置を保存
	XMFLOAT2 map = {-1,-1};
	int Status = 0;
};