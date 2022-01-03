#pragma once
#include <dinput.h>
#include <DirectXMath.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
enum ButtonKind
{
	ButtonUp,
	ButtonDown,
	ButtonLeft,
	ButtonRight,
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	ButtonKindMax,
};

enum ButtonState
{
	ButtonStateNone,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
};

class Controller
{
private:
	// �Q�[���p�b�h�̓��͏��擾
	DIJOYSTATE pad_data;
	DIJOYSTATE oldpad_data;
	LPDIRECTINPUTDEVICE8 g_GamePadDevice = nullptr;
	LPDIRECTINPUT8 g_InputInterface = nullptr;
public://�Q�[���p�b�h

//* @brief Input�@�\�������֐�@n
//* �f�o�C�X�̓��͎擾�ɕK�v�ȏ��������s��
//* ��InitEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂Ȃ�
//* @return ����������(������true)

	bool InitController();

	/*
	* @brief Input�@�\�I���֐�@n
	* Input�@�\���I��������@n
	*/
	void ReleaseInput();

	/*
	* @brief ���͏��̍X�V@n
	* �f�o�C�X�̓��͏��̍X�V���s��@n
	* ���t���[���ɂP�x�K�����s����K�v������
	*/
	void UpdateInput();

	/*
	* @brief �{�^����������Ă��邩�̔���֐�
	* @retval true�F������Ă���
	* @retval false�F������Ă��Ȃ�
	* @param[in] button ���肵�����{�^���̎��
	*/
	bool IsButtonPush(ButtonKind button);

	/*
	* @brief �{�^���������ꂽ�u�Ԃ̔���֐�
	* @retval true�F�������u��
	* @retval false�F�������u�Ԃł͂Ȃ�
	* @param[in] button ���肵�����{�^���̎��
	*/
	bool IsButtonUp(ButtonKind button);

	/*
	* @brief �{�^���𗣂����u�Ԃ̔���֐�
	* @retval true�F�������u��
	* @retval false�F�u�Ԃł͂Ȃ�
	* @param[in] button ���肵�����{�^���̎��
	*/
	bool IsButtonDown(ButtonKind button);

};