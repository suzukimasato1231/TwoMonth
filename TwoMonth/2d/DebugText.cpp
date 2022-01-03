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
	//�X�v���C�g
	sprite = new Sprite();
	if (sprite == nullptr)
	{
		assert(sprite);
	}
	sprite->Init();

	// �S�ẴX�v���C�g�f�[�^�ɂ���
	for (int i = 0; i < _countof(sprites); i++)
	{
		// �X�v���C�g�𐶐�����
		sprites[i] = sprite->SpriteCreate(L"Resources/debugfont.png");
	}
}
// 1������ǉ�
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

	// �S�Ă̕����ɂ���
	for (size_t i = 0; text[i] != '\0'; i++)
	{
		// �ő啶��������
		if (spriteIndex >= maxCharCount) {
			break;
		}

		// 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char &character = text[i];

		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;



		// ���W�v�Z
		sprites[spriteIndex].position = { x + fontWidth * size * i, y ,0 };

		sprites[spriteIndex].texLeftTop = { (float)fontIndexX * fontWidth,(float)fontIndexY * fontHeight };

		sprites[spriteIndex].texSize = { fontWidth,fontHeight };

		sprites[spriteIndex].size = { fontWidth * size, fontHeight * size };

		//���_�o�b�t�@�]��
		sprite->SpriteTransferVertexBuffer(sprites[spriteIndex]);

		//�X�V
		sprite->DebugUpdate(sprites[spriteIndex]);

		// �������P�i�߂�
		spriteIndex++;
	}
}

void DebugText::DrawAll()
{
	sprite->PreDraw();
	// �S�Ă̕����̃X�v���C�g�ɂ���
	for (size_t i = 0; i < spriteIndex; i++)
	{
		// �X�v���C�g�`��
		sprite->DebugDraw(sprites[i]);
	}
	spriteIndex = 0;
}

