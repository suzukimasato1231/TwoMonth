#include "Input.h"

void Input::Initialize(_Window *win)
{
	//キーボード初期化
	keybord.Initialize(win);

	//コントローラー初期化
	controller.InitController();

	//マウス初期化
	mouse.Init(win);
}

void Input::Update()
{
	//キーボード更新	
	keybord.Update();
	//コントローラー更新
	controller.UpdateInput();
	//マウス更新
	mouse.Update();
}


bool Input::KeybordPush(BYTE keyNumber)
{
	return keybord.PushKey(keyNumber);
}

bool Input::KeybordTrigger(BYTE keyNumber)
{
	return keybord.TriggerKey(keyNumber);
}

bool Input::ControllerPush(ButtonKind button)
{
	return controller.IsButtonPush(button);
}

bool Input::ControllerUp(ButtonKind button)
{
	return controller.IsButtonUp(button);
}

bool Input::ControllerDown(ButtonKind button)
{
	return controller.IsButtonDown(button);
}

bool Input::MousePushLeft()
{
	return mouse.PushMouseLeft();
}

bool Input::MousePushMiddle()
{
	return mouse.PushMouseMiddle();
}

bool Input::MouseTriggerLeft()
{
	return mouse.TriggerMouseLeft();
}

bool Input::MouseTriggerMiddle()
{
	return mouse.TriggerMouseMiddle();
}

Mouse::MouseMove Input::GetMouseMove()
{
	return mouse.GetMouseMove();
}

