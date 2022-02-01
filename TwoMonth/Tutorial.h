#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<time.h>
time_t time(time_t *);
extern const int window_width;
extern const int window_height;
enum TUTORIAL
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
};

class Tutorial
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
public:
	Tutorial();
	~Tutorial();
	//初期化
	void Init(Input *input, Sprite *sprite);
	//メイン初期化
	void MainInit();
	//更新
	void Update();
	//描画
	void Draw();
	//チュートリアルフラグを獲得
	bool GetTutorialFlag();
	//チュートリアルフラグをfalseにする
	void TutorialFlagChange();
	//チュートリアルの説明が終わったかどうかフラグを獲得
	bool GetTutorialEndFlag();
	//長押しでスキップ
	bool Longpress();
	//長押ししてない
	void NotLongpress();
private:
	//チュートリアルをしているかどうか
	bool tutorialFlag = true;
	//チュートリアルの説明が終わったかどうか
	bool tutorialEndFlag = false;

	Sprite::SpriteData Explanation1;//説明画像1
	Sprite::SpriteData Explanation2;//説明画像2
	Sprite::SpriteData Explanation3;//説明画像3
	Sprite::SpriteData Explanation4;//説明画像4
	Sprite::SpriteData Explanation5;//説明画像5
	Sprite::SpriteData Explanation6;//説明画像6
	Sprite::SpriteData Explanation7;//説明画像7
	Sprite::SpriteData Explanation8;//説明画像8


	Sprite::SpriteData numGraph[10];

	XMFLOAT2 position = { 0.0f, 180.0f };//座標

	//チュートリアルを飛ばすボタンの表示
	Sprite::SpriteData SkipTutorialGraph;
	//チュートリアル中の何番目か	
	int tutorialScene = ONE;
	//チュートリアルが変わる最大時間
	const int timeMax = 400;
	//現在のチュートリアルの時間
	int tutorialTime = 0;
	//時間計測
	time_t start_time, end_time;
	bool timeFlag = false;

};