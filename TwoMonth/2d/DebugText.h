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
	// デバッグテキスト用のテクスチャ番号を指定
	static const int maxCharCount = 512;	// 最大文字数
	static const int fontWidth = 9;			// フォント画像内1文字分の横幅
	static const int fontHeight = 18;		// フォント画像内1文字分の縦幅
	static const int fontLineCount = 14;	// フォント画像内1行分の文字数

	DebugText();
	~DebugText();

	void Initialize();
	  
	/// <summary>
	///  デバックテキスト
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="size">サイズ</param>
	/// <param name="text">表示する文字</param>
	/// <param name=""></param>
	void Print(float x, float y, float size, std::string text, ...);

	void DrawAll();

private:
	Sprite *sprite = nullptr;

	// スプライトデータの配列
	Sprite::SpriteData sprites[maxCharCount] = {};
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
};
