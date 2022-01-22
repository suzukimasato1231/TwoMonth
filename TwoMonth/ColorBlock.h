#pragma once
#include"2d/Sprite.h"
#include"3d/Object.h"
#include"base/Safe_delete.h"
#include"base/XMFLOATHelper.h"
#include"Table.h"
enum BlockColor
{
	Red = 1,
	Yellow,
	Blue,
	//土台
	Foundation,
};
class ColorBlock
{
private:
	Object *object = nullptr;
public:
	ColorBlock();
	~ColorBlock();

	void Init(Object::ObjectData block, Object::ObjectData block2, Object::ObjectData block3,
		Object::ObjectData block4, Object::ObjectData block5, Object::ObjectData block6,
		Object::ObjectData block7, Object::ObjectData block8, Object::ObjectData block9, Object *object, int color, int redGraph, int yellowGraph, int blueGraph);
	//更新
	void Update();
	//描画
	void Draw();
	//親クラスを取得
	void GetSpriteParent(Object::ObjectData *parent);
	//押し戻し処理
	void PushBack(int isHit, const float blockSize);

	//ブロック加速
	void SpeedUpdate();
	XMFLOAT3 GetPos();

	XMFLOAT3 GetoldPos();

	bool GetFlag();
	//マップチップ内の情報を保存、台の上での座標を入れる
	void Pos(int i, int j, int direction, const float blockSize);
	//下にブロックがないときの座標を入れる
	void ShiftPos(int i, int j, int direction, const float blockSize);
	XMFLOAT2 Getmap();

	int GetStatus();

	int GetColor();

	int GetLevel();
	//レベル上昇
	void LevelUP(int i);

	bool GetDeleteFlag();
	//フラグをTRUEにする
	void BreakFlagTRUE();
	//敵を挟む
	void Sandwich();

	bool GetBreakFlag();
private:
	Object::ObjectData block[9];
	int redGraph = 0; 
	int yellowGraph = 0;
	int blueGraph = 0; 
	XMFLOAT3 pos{ 0.0f,400.0f,-51.0f };
	XMFLOAT3 oldPos{};
	XMFLOAT3 rotation{};
	bool Flag = true;//台に乗ってるかどうか
	int color = 0;//色
	//マップチップの位置を保存
	XMFLOAT2 map = { -1,-1 };
	int Status = 0;

	int Level = 1;

	//ブロックが挟むフラグ
	bool  blockBreakFlag = false;
	bool  DeleteFlag = false;
	//敵を挟むまでの時間
	int time = 20;
};