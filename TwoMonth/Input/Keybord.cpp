#include"Keybord.h"
void Keybord::Initialize(_Window *win)
{
	HRESULT result;
	//キーボード入力
	result = DirectInput8Create(
		win->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);

	//キーボードデバイスの生成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(
		win->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Keybord::Update()
{
	HRESULT result;
	// DirectX毎フレーム処理　ここから
	for (int i = 0; i < 256; i++)
	{
		oldkey[i] = key[i];
	}
	//キーボード情報の取得開始
	result = devkeyboard->Acquire();
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Keybord::PushKey(BYTE keyNumber)
{
	// 0でなければ押している
	if (key[keyNumber]) {
		return true;
	}
	// 押していない
	return false;
}

bool Keybord::TriggerKey(BYTE keyNumber)
{
	// 前回が0で、今回が0でなければトリガー
	if (!oldkey[keyNumber] && key[keyNumber]) {
		return true;
	}
	// トリガーでない
	return false;
}

