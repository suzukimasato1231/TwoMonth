#pragma once
#include"Controller.h"
#include "Keybord.h"
#include "Mouse.h"
class Input
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private://メンバ変数
	//キーボード
	Keybord keybord;
	//コントローラー
	Controller controller;
	//マウス
	Mouse mouse;
public://メンバ関数
	//初期化
	void Initialize(_Window *win);
	//更新
	void Update();
public://キーボード
	//押してる時
	bool KeybordPush(BYTE keyNumber);
	//押した瞬間
	bool KeybordTrigger(BYTE keyNumber);
public://ゲームパッド

	//@brief ボタンが押されているかの判定関数
	// @param[in] button 判定したいボタンの種類
	bool ControllerPush(ButtonKind button);

	// @brief ボタンが押された瞬間の判定関数
	// @param[in] button 判定したいボタンの種類
	bool ControllerUp(ButtonKind button);

	// @brief ボタンを離した瞬間の判定関数
	// @param[in] button 判定したいボタンの種類
	bool ControllerDown(ButtonKind button);
public://マウス
	bool MousePushLeft();

	/// <summary>
	/// キーの中ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool MousePushMiddle();

	/// <summary>
	/// キーの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool MouseTriggerLeft();

	/// <summary>
	/// キーの中ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool MouseTriggerMiddle();

	/// <summary>
	/// マウス移動量を取得
	/// </summary>
	/// <returns>マウス移動量</returns>
	Mouse::MouseMove GetMouseMove();
};