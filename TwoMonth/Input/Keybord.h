#pragma once
//キーボード入力
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#include<wrl.h>
#include <DirectXMath.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include"../base/_Window.h"
class Keybord
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private://メンバ変数
	//全キーの入力状態を取得
	BYTE key[256];
	//1つ前の入力状態を取得
	BYTE oldkey[256];
	//キーボード入力
	ComPtr<IDirectInput8> dinput = nullptr;
	//キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> devkeyboard = nullptr;
public://メンバ関数
	//初期化
	void Initialize(_Window *win);
	//更新
	void Update();

	//押した瞬間
	bool PushKey(BYTE keyNumber);
	//離した瞬間
	bool TriggerKey(BYTE keyNumber);
};