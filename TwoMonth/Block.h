#pragma once
#include"2d/Sprite.h"
#include"3d/Object.h"
#include"Input/Input.h"
#include<vector>
#include<time.h>
#include"ColorBlock.h"
#include"base/Safe_delete.h"
#include"collision/Collision.h"
#include"Table.h"
#include"Particle.h"
time_t time(time_t *);
const int mapNum = 20;

class Block
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
	Object *object = nullptr;
public:
	Block();

	~Block();

	//プレイヤーが置ける秒数
	time_t start_player, end_player;//時間計測
	bool playerTimeFlag = false;//プレイヤーターンフラグ


	//初期化
	void Init(Input *input, Sprite *sprite, Object *object);
	//ゲームループの初期化
	void MainInit();
	//更新
	void Update(Object::ObjectData *table, int direction);
	//描画
	void Draw();
	//UI描画
	void DrawUI();
	//ブロックと台の当たり判定
	void ColBlock(Object::ObjectData *table, XMFLOAT3 tablePos, int direction);
	//ダメージ
	void Damege();
	//ブロックとマップチップ初期化
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

	int GetGameOverCount(int i);

	bool GetGameOverFlag();

	bool GetShakeFlag();

	bool GetSandEndFlag();

	bool GetPutFlag();
	//ブロックを消す
	void SandwitchDelete();

	//ブロック置きすぎの警告を描画する
	void WallningDraw();
	//ゲームオーバーまでのカウントの描画
	void DrawGameOverCount();
	//挟んだ時の演出の更新
	void RockUpdate();
	//挟んだ時の演出の描画
	void RockDraw();

	bool GetPlayerTimeFlag();

	int GetPTime();
private:
	//ブロック追加
	void AddBlock(int direction);
	//ブロック移動
	void MoveBlock(Object::ObjectData *table, int direction);
	/// <summary>
	/// ブロックをずらす
	/// </summary>
	/// <param name="i">マップチップのｘ</param>
	/// <param name="j">マップチップのｙ</param>
	void BlockShift(int i, int j);

	//ハードドロップ
	void HardDrop();
	//回転時のブロックの処理
	void BlockSetRot(Object::ObjectData *table, int direction);
	//ブロック結合
	void BlockJoin();
	//ゲームオーバーまでの時間を計測
	void CountGamaeOverTime();
	//ブロックがあふれたかどか
	void Overflow();

	//挟まったマップチップの位置を０にする
	void MapDelete();

	void PlayerTime();
private:
	std::vector<ColorBlock *>colorBlock;

	Sprite::SpriteData blocknext[9];
	Object::ObjectData block[9];
	//画像
	int blueGraph = 0;
	int redGraph = 0;
	int yellowGraph = 0;

	//ブロックのマップチップ
	int mapUP[mapNum];//上の状態
	int mapDown[mapNum];//下の状態
	int mapLeft[mapNum];//左の状態
	int mapRight[mapNum];//右の状態

	int oldmapUP[mapNum];//上の状態
	int oldmapDown[mapNum];//下の状態
	int oldmapLeft[mapNum];//左の状態
	int oldmapRight[mapNum];//右の状態

	const float blockSize = 30.0f;
	//マップチップのXの残滓
	const int blockX = 5;
	//色のデータ保持
	int memoryColor = 1;

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

	const int mapoverY = 8;				//おけるブロックの最大数
	time_t start_time[4], end_time[4];//時間計測
	bool blockOverFlag[4] = {};//ブロックをオーバーしたかどうか
	int gameOverCount[4] = { 0,0,0,0 };	//ゲームオーバータイムカウント
	bool gameOverFlag = false;//ゲームーオーバー
	const int gameOverTimeMax = 5;//オーバータイム（５ｓ）

	Object::ObjectData warningNumber;//ブロック置きすぎ警告数字
	int warningNumberGraph[9];
	Object::ObjectData warningWall;		//警告の赤いシート
	int warningGraph = 0;//赤い枠画像
	Object::ObjectData outWarningWall;
	int outWarningGraph = 0;//赤いシート画像外側
	int outWarningTime = 0;


	bool ShakeFlag = false;//シェイクフラグ

	//ブロックが壊れるパーティクル
	vector<Particle *>rock;
	Object::ObjectData rockPolygon;
	int rockGraph;

	//設置フラグ
	bool putFlag = false;
};