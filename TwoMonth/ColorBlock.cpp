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
		//pos.y += 1.0f;
		pos.y += 0.1f;
	}
}

void ColorBlock::Draw()
{
	switch (color)
	{
	case Red:
		sprite->Draw(block, XMFLOAT2(pos.x - 120.0f, pos.y), 300.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case Yellow:
		sprite->Draw(block, XMFLOAT2(pos.x - 120.0f, pos.y), 300.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Blue:
		sprite->Draw(block, XMFLOAT2(pos.x - 120.0f, pos.y), 300.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	}
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
		pos.x = -i * blockSize + 120 - blockSize;
		pos.y = 150 + j * blockSize;
		break;
	case Left:
		pos.x = -j * blockSize - blockSize;
		pos.y = i * blockSize - blockSize - 240;
		block.rotation += 90.0f;
		break;
	case Right:
		pos.x = j * blockSize + 300;
		pos.y = i * blockSize - 270;
		block.rotation += 90.0f;
		break;
	}
	//マップの位置を保存
	map = { (float)i,(float)j + 1 };
	Status = direction;
}

void ColorBlock::ShiftPos(int i, int j, int direction, const float blockSize)
{
	switch (direction)
	{
	case UP:
		pos.x = i * blockSize - 180;
		pos.y = -150 - blockSize - j * blockSize;
		break;
	case Down:
		pos.x = -i * blockSize + 150 - blockSize;
		pos.y = 150 + j * blockSize;
		break;
	case Left:
		pos.x = -j * blockSize - blockSize;
		pos.y = i * blockSize - blockSize - 270;
		break;
	case Right:
		pos.x = j * blockSize + 300;
		pos.y = i * blockSize - 300;
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
