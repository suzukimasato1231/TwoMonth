#include "DebugText.h"

DebugText::DebugText()
{

}

DebugText::~DebugText()
{
	safe_delete(sprite);
}

void DebugText::Initialize()
{
	//スプライト
	sprite = new Sprite();
	if (sprite == nullptr)
	{
		assert(sprite);
	}
	sprite->Init();

	// 全てのスプライトデータについて
	for (int i = 0; i < _countof(sprites); i++)
	{
		// スプライトを生成する
		sprites[i] = sprite->SpriteCreate(L"Resources/debugfont.png");
	}
}
// 1文字列追加
void DebugText::Print(float x, float y, float size, std::string text, ...)
{
	bool parsentFlag = false;
	va_list args;
	va_start(args, text);
	text.push_back(' ');
	for (size_t i = 0; text[i] != '\0'; ++i)
	{
		printf("%c:", text[i]);
		if (text[i] == '%')
		{
			parsentFlag = true;
		}
		if (parsentFlag == true)
		{
			int temp;
			double tempF = NULL;
			switch (text[i])
			{
			case 'd':
				temp = va_arg(args, int);
				text.replace((size_t)i - 1, 2, std::to_string(temp));
				parsentFlag = false;
				break;
			case 'f':
				tempF = va_arg(args, double);
				tempF = round(tempF * 100);
				tempF = tempF / 100;
				text.replace((size_t)i - 1, 2, std::to_string(tempF));
				parsentFlag = false;
				break;
			default:
				break;
			}
		}
	}
	va_end(args);

	// 全ての文字について
	for (size_t i = 0; text[i] != '\0'; i++)
	{
		// 最大文字数超過
		if (spriteIndex >= maxCharCount) {
			break;
		}

		// 1文字取り出す(※ASCIIコードでしか成り立たない)
		const unsigned char &character = text[i];

		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;



		// 座標計算
		sprites[spriteIndex].position = { x + fontWidth * size * i, y ,0 };

		sprites[spriteIndex].texLeftTop = { (float)fontIndexX * fontWidth,(float)fontIndexY * fontHeight };

		sprites[spriteIndex].texSize = { fontWidth,fontHeight };

		sprites[spriteIndex].size = { fontWidth * size, fontHeight * size };

		//頂点バッファ転送
		sprite->SpriteTransferVertexBuffer(sprites[spriteIndex]);

		//更新
		sprite->DebugUpdate(sprites[spriteIndex]);

		// 文字を１つ進める
		spriteIndex++;
	}
}

void DebugText::DrawAll()
{
	sprite->PreDraw();
	// 全ての文字のスプライトについて
	for (size_t i = 0; i < spriteIndex; i++)
	{
		// スプライト描画
		sprite->DebugDraw(sprites[i]);
	}
	spriteIndex = 0;
}

