#include "ColorBlock.h"

ColorBlock::ColorBlock() {}

ColorBlock::~ColorBlock() {}

void ColorBlock::Init(Sprite::SpriteData block, Sprite *sprite)
{
	this->block = block;
	assert(sprite);
	this->sprite = sprite;
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
	sprite->Draw(block, pos, 30.0f, 30.0f);
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

void ColorBlock::PushBack(XMFLOAT2 mapChip, int isHit)
{
	pos.x -= 30;
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

void ColorBlock::Pos(int i, int j, int direction)
{
	switch (direction)
	{
	case UP:
		pos.x = i * 30 - 150;
		pos.y = -150 - 30 - j * 30;
		break;
	case Down:
		pos.x = -i * 30 + 150 - 30;
		pos.y = 150 + j * 30;
		break;
	case Left:
		pos.x = -150 - j * 30 - 30;
		pos.y = +150 - i * 30 - 30;
		break;
	case Right:
		pos.x = 150 + j * 30;
		pos.y = -150 + i * 30;
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
