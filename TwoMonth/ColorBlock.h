#pragma once
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
	//現在の座標を取得
	XMFLOAT3 GetPos();
	//１つ前の座標を取得
	XMFLOAT3 GetoldPos();
	//台に乗っているかのフラグを取得
	bool GetMoveFlag();
	//マップチップ内の情報を保存、台の上での座標を入れる
	void Pos(int i, int j, int direction, const float blockSize);
	//下にブロックがないときの座標を入れる
	void ShiftPos(int i, int j, int direction, const float blockSize);
	//マップチップ位置取得
	XMFLOAT2 Getmap();
	//上下左右のどれか取得
	int GetStatus();
	//色を取得
	int GetColor();
	//重なった数を取得
	int GetLevel();
	//レベル上昇
	void LevelUP(int i);
	//消えるかどうかのフラグを取得
	bool GetDeleteFlag();
	//フラグをTRUEにする
	void BreakFlagTRUE();
	//敵を挟む
	void Sandwich();
	//ブロックを挟むフラグを取得
	bool GetBreakFlag();
private:
	Object::ObjectData block[9];		//ブロックのオブジェクトデータ
	int redGraph = 0;					//赤のブロックの画像データ位置
	int yellowGraph = 0;				//黄色のブロックの画像データ位置
	int blueGraph = 0;					//青のブロックの画像データ位置
	XMFLOAT3 pos{ 0.0f,400.0f,-51.0f };	//現在の座標
	XMFLOAT3 oldPos{};					//1つ前の座標
	XMFLOAT3 rotation{};				//回転位置
	bool moveFlag = true;				//台に乗ってるかどうか
	int color = 0;						//色
	XMFLOAT2 map = { -1,-1 };			//マップチップのどの位置か
	int Status = 0;						//上下左右のどこか
	int Level = 1;						//重なってる数

	bool  blockBreakFlag = false;		//ブロックが挟むフラグ
	bool  DeleteFlag = false;			//消えるかどうか
	int time = 20;						//敵を挟むまでの時間
};