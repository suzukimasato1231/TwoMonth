#pragma once
#include<Windows.h>
#include<vector>
#include<string>
#include<d3d12.h>
#include<dxgi1_6.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
extern const int window_width;
extern const int window_height;
class _Window
{
public://メンバ関数
	void CreateGameWindow();

	//メッセージ処理
	bool ProcessMessage();

	//ゲームウィンドウの破棄
	void TerminateGameWindow();

	//Hwnd獲得
	HWND GetHwnd() { return hwnd; }

	//w.hInstance獲得
	HINSTANCE GetInstance() { return w.hInstance; }

private://メンバ変数
	// ウィンドウオブジェクトの生成
	HWND hwnd = nullptr;
	WNDCLASSEX w{};//ウィンドウクラスの設定

	
};