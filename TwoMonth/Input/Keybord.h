#pragma once
//�L�[�{�[�h����
#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��
#include<dinput.h>
#include<wrl.h>
#include <DirectXMath.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include"../base/_Window.h"
class Keybord
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private://�����o�ϐ�
	//�S�L�[�̓��͏�Ԃ��擾
	BYTE key[256];
	//1�O�̓��͏�Ԃ��擾
	BYTE oldkey[256];
	//�L�[�{�[�h����
	ComPtr<IDirectInput8> dinput = nullptr;
	//�L�[�{�[�h�f�o�C�X�̐���
	ComPtr<IDirectInputDevice8> devkeyboard = nullptr;
public://�����o�֐�
	//������
	void Initialize(_Window *win);
	//�X�V
	void Update();

	//�������u��
	bool PushKey(BYTE keyNumber);
	//�������u��
	bool TriggerKey(BYTE keyNumber);
};