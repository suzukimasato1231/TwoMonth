#include "ColorBlock.h"

ColorBlock::ColorBlock() {}

ColorBlock::~ColorBlock() {}

void ColorBlock::Init(Sprite::SpriteData block, Sprite *sprite)
{
	this->block = block;
	assert(sprite);
	this->sprite = sprite;

	color = rand() % 3 + 1;
}

void ColorBlock::Update()
{
	oldPos = pos;
	if (Flag == true)
	{
		pos.y += 1.0f;
	}
}

void ColorBlock::Draw()
{
	switch (color)
	{
	case Red:
		sprite->Draw(block, pos, 30.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case Yellow:
		sprite->Draw(block, pos, 30.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Blue:
		sprite->Draw(block, pos, 30.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	}
}

void ColorBlock::LeftMove()
{
	pos.x -= 30.0f;
}

void ColorBlock::RightMove()
{
	pos.x += 30.0f;
}

void ColorBlock::GetSpriteParent(Sprite::SpriteData *parent)
{
	assert(parent);
	block.parent = parent;

	Flag = false;
}

void ColorBlock::PushBack(int isHit, const float blockSize)
{
	if (isHit == 2)
	{
		pos.x -= blockSize;
	}
	if (isHit == 3)
	{
		pos.x += blockSize;
	}

}

XMFLOAT2 ColorBlock::GetPos()
{
	return pos;
}

XMFLOAT2 ColorBlock::GetoldPos()
{
	return oldPos;
}

bool ColorBlock::GetFlag()
{
	return Flag;
}

void ColorBlock::Pos(int i, int j, int direction, const float blockSize)
{
	switch (direction)
	{
	case UP:
		pos.x = i * blockSize - 150;
		pos.y = -150 - blockSize - j * blockSize;
		break;
	case Down:
		pos.x = -i * blockSize + 150 - blockSize;
		pos.y = 150 + j * blockSize;
		break;
	case Left:
		pos.x = -150 - j * blockSize - blockSize;
		pos.y = +150 - i * blockSize - blockSize;
		break;
	case Right:
		pos.x = 150 + j * blockSize;
		pos.y = -150 + i * blockSize;
		break;
	}
	//マップの位置を保存
	map = { (float)i,(float)j + 1 };
	Status = direction;
}

XMFLOAT2 ColorBlock::Getmap()
{
	return map;
}

int ColorBlock::GetStatus()
{
	return Status;
}

int ColorBlock::GetColor()
{
	return color;
}
