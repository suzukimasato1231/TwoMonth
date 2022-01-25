#pragma once
#pragma once
#include <DirectXMath.h>
#include"2d/Sprite.h"
#include"base/XMFLOATHelper.h"
extern const int window_width;
extern const int window_height;
class SceneChange
{
	using XMFLOAT4 = DirectX::XMFLOAT4;
private:
	Sprite *sprite = nullptr;
public://シーンチェンジ
	void Init(Sprite *sprite);
	//色取得
	XMFLOAT4 GetColor();
	//シーンチェンジ中
	bool GetChangeFlag();
	//シーンチェンジ前半終了したか
	bool Change();
	//シーンチェンジ演出スタート
	void Start();
	//シーンチェンジ更新
	void Update();
	//描画
	void Draw();
private:
	Sprite::SpriteData SceneGraph;
	bool sceneChangeFlag;//暗転しているか
	bool firstHalfFlag;//演出の前半かどうか
	XMFLOAT4 changeColor;
private://フェーズクリア
	Sprite::SpriteData phaseClearGraph;
	XMFLOAT3 phaseStart;				//スタート地点
	XMFLOAT3 phaseEnd;				//エンド地点
	float phaseEasingTime;
	float phaseMaxTime;				//全体時間[s]
	float phaseTimeRate;			//何％　時間が進んだか(率)
	bool phaseFlag = true;
public:
	//スコアイージング/スタート位置、終了位置、進む時間
	void phaseEasingStart(XMFLOAT3 start, XMFLOAT3 end, float Time);
	//スコアイージング更新
	XMFLOAT3 phaseEasing();

	void DrawPhase();

	void ChangePhaseFlag();
private://ゲームオーバー
	Sprite::SpriteData gameOverGraph;
	bool gameoverFlag = true;
public:
	//スコアイージング/スタート位置、終了位置、進む時間
	void gameoverasingStart(XMFLOAT3 start, XMFLOAT3 end, float Time);
	//スコアイージング更新
	XMFLOAT3 gameoverEasing();

	void ChangePhasegameoverFlag();

	void DrawGameOver();
};


//補間関数
//線形補間
const XMFLOAT3 lerp(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);
const XMFLOAT3 easeIn(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);
const XMFLOAT3 easeOut(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);
const XMFLOAT3 easeInOut(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t);