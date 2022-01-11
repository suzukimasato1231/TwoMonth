#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<vector>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
const int mapNum = 10;

class Block
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
public:
	Block();

	~Block();

	void Init(Input *input, Sprite *sprite);

	void Update();

	void Draw();

	//ブロックと台の当たり判定
	void ColBlock(Sprite::SpriteData *table,XMFLOAT2 tablePos,int direction);
	//ダメージ
	void Damege();

	bool GetDameFlag();
private:
	//ブロック追加
	void AddBlock();
	//ブロック移動
	void MoveBlock();
	/// <summary>
	/// ブロックをずらす
	/// </summary>
	/// <param name="i">マップチップのｘ</param>
	/// <param name="j">マップチップのｙ</param>
	void BlockShift(int i, int j);

private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData block;

	//ブロックのマップチップ
	int mapUP[10][mapNum];//上の状態
	int mapDown[10][mapNum];//下の状態
	int mapLeft[10][mapNum];//左の状態
	int mapRight[10][mapNum];//右の状態

	const float blockSize = 30.0f;

	bool DamegeFlag = false;
};