#include<Windows.h>
#include"base/_Window.h"
#include"base/_DirectX.h"
#include"base/Safe_delete.h"
#include"Sound/Sound.h"
#include"Input/Input.h"
#include"GameSceneManager.h"
#include"2d/Sprite.h"
#include"2d/DebugText.h"
const int window_width = 1280;//横幅
const int window_height = 720;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//汎用機能
	_Window *win = nullptr;
	Input *input = nullptr;
	_DirectX *directX = nullptr;
	GameSceneManager *gameScene = nullptr;
	Sprite *sprite = nullptr;
	DebugText *debugText = nullptr;
	//ゲームウィンドウの作成
	win = new _Window();
	input = new Input();
	directX = new _DirectX();
	win->CreateGameWindow();

	// DirectX初期化処理
	directX->Initilize(win);
	input->Initialize(win);
#pragma region 描画初期化処理	
	//ライト静的初期化
	Light::StaticInitialize(directX->GetDevice());
	//スプライト静的初期化
	Sprite::StaticInit(directX->GetDevice(), directX->GetCmandList());
	

	//ゲームシーン
	gameScene = new GameSceneManager();
	gameScene->Initialize(input, directX);
	gameScene->Init();

	while (true)  // ゲームループ
	{
		//メッセージ処理
		if (win->ProcessMessage()) { break; }

		input->Update();

		gameScene->Update();

		//描画開始
		directX->PreDraw();

		gameScene->Draw(*directX);

		directX->ResourceBarrier();
		//描画コマンドはここまで
	}
#pragma region	//データ解放
	//XAudio2解放
	safe_delete(input);
	safe_delete(gameScene);
	safe_delete(directX);
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}
