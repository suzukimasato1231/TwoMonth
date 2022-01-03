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
public://�����o�֐�
	void CreateGameWindow();

	//���b�Z�[�W����
	bool ProcessMessage();

	//�Q�[���E�B���h�E�̔j��
	void TerminateGameWindow();

	//Hwnd�l��
	HWND GetHwnd() { return hwnd; }

	//w.hInstance�l��
	HINSTANCE GetInstance() { return w.hInstance; }

private://�����o�ϐ�
	// �E�B���h�E�I�u�W�F�N�g�̐���
	HWND hwnd = nullptr;
	WNDCLASSEX w{};//�E�B���h�E�N���X�̐ݒ�

	
};