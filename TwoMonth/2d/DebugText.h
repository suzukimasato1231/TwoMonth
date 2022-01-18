#pragma once
#include "Sprite.h"
#include "../base/Safe_delete.h"
#include <stdio.h>
#include <stdarg.h>
extern const int window_width;
extern const int window_height;

class DebugText
{
public:
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	static const int maxCharCount = 512;	// �ő啶����
	static const int fontWidth = 9;			// �t�H���g�摜��1�������̉���
	static const int fontHeight = 18;		// �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;	// �t�H���g�摜��1�s���̕�����

	DebugText();
	~DebugText();

	void Initialize();
	  
	/// <summary>
	///  �f�o�b�N�e�L�X�g
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="size">�T�C�Y</param>
	/// <param name="text">�\�����镶��</param>
	/// <param name=""></param>
	void Print(float x, float y, float size, std::string text, ...);

	void DrawAll();

private:
	Sprite *sprite = nullptr;

	// �X�v���C�g�f�[�^�̔z��
	Sprite::SpriteData sprites[maxCharCount] = {};
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;
};
