#include"Mouse.h"
#include <cassert>



bool Mouse::Init(_Window *win)
{
	HRESULT result = S_FALSE;

	// DirectInputオブジェクトの生成	
	result = DirectInput8Create(win->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// マウスデバイスの生成	
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // 標準形式
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(win->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}
	return true;
}

void Mouse::Update()
{
	HRESULT result;
	result = devMouse->Acquire();	// マウス動作開始

	// 前回の入力を保存
	mouseStatePre = mouseState;

	// マウスの入力
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

bool Mouse::PushMouseLeft()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[0]) {
		return true;
	}

	// 押していない
	return false;
}

bool  Mouse::PushMouseMiddle()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	// 押していない
	return false;
}

bool  Mouse::TriggerMouseLeft()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool  Mouse::TriggerMouseMiddle()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
		return true;
	}

	// トリガーでない
	return false;
}

Mouse::MouseMove  Mouse::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouseState.lX;
	tmp.lY = mouseState.lY;
	tmp.lZ = mouseState.lZ;
	return tmp;
}
