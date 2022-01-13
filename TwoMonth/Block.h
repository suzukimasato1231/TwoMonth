#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<vector>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
const int mapNum = 20;

class Block
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
public:
	Block();

	~Block();

	void Init(Input *input, Sprite *sprite);

	void Update(Sprite::SpriteData *table, int direction);

	void Draw();

	//ブロックと台の当たり判定
	void ColBlock(Sprite::SpriteData *table,XMFLOAT2 tablePos,int direction);
	//ダメージ
	void Damege();

	void DeleteBlock();

	bool GetDameFlag();

	bool GetCheckFlag();

	bool GetAddFlag();

	int GetSandDelay();

	int GetComboCount();

	int GetColorNumUp();
	int GetColorNumDown();
	int GetColorNumLeft();
	int GetColorNumRight();

	void SetSandDelay(int count);
private:
	//ブロック追加
	void AddBlock();
	//ブロック移動
	void MoveBlock(Sprite::SpriteData *table, int direction);
	/// <summary>
	/// ブロックをずらす
	/// </summary>
	/// <param name="i">マップチップのｘ</param>
	/// <param name="j">マップチップのｙ</param>
	void BlockShift(int i, int j);

	//ハードドロップ
	void HardDrop(Sprite::SpriteData *table, int direction);
	//回転時のブロックの処理
	void BlockSetRot(Sprite::SpriteData *table, int direction);
	//レベルに合わせてマップチップ初期化
	void LevelDelete(int direction, int blockNum, int mapY);
	//ブロック結合
	void BlockJoin();
private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData block[3];

	//ブロックのマップチップ
	int mapUP[mapNum];//上の状態
	int mapDown[mapNum];//下の状態
	int mapLeft[mapNum];//左の状態
	int mapRight[mapNum];//右の状態

	const float blockSize = 30.0f;
	//マップチップのXの残滓
	const int blockX = 5;
	bool DamegeFlag = false;

	bool addFlag = false;

	int sandDelay = 0;
	bool sandFlag = 0;

	int comboCount = 0;

	bool checkFlag = 0;
	int checkColorUp = 0;
	int checkColorDown = 0;
	int checkColorLeft = 0;
	int checkColorRight = 0;
};