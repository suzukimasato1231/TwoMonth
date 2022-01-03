#include"Keybord.h"
void Keybord::Initialize(_Window *win)
{
	HRESULT result;
	//�L�[�{�[�h����
	result = DirectInput8Create(
		win->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);

	//�L�[�{�[�h�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(
		win->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Keybord::Update()
{
	HRESULT result;
	// DirectX���t���[�������@��������
	for (int i = 0; i < 256; i++)
	{
		oldkey[i] = key[i];
	}
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Keybord::PushKey(BYTE keyNumber)
{
	// 0�łȂ���Ή����Ă���
	if (key[keyNumber]) {
		return true;
	}
	// �����Ă��Ȃ�
	return false;
}

bool Keybord::TriggerKey(BYTE keyNumber)
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!oldkey[keyNumber] && key[keyNumber]) {
		return true;
	}
	// �g���K�[�łȂ�
	return false;
}

