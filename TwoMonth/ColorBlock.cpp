#include "ColorBlock.h"

ColorBlock::ColorBlock() {}

ColorBlock::~ColorBlock() {}

void ColorBlock::Init(Sprite::SpriteData block, Sprite::SpriteData block2, Sprite::SpriteData block3, Sprite *sprite, int color)
{
	this->block[0] = block;
	this->block[1] = block2;
	this->block[2] = block3;
	assert(sprite);
	this->sprite = sprite;

	this->color = color;
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
	int ofsetY = 0, ofsetX = 0;
	if (Status == Down)
	{
		ofsetY = 30 * (Level - 1);
	}
	if (Status == Left)
	{
		ofsetY = 30 * (Level - 1);
	}
	if (Status == Right)
	{
		ofsetY = 30 * (Level - 1);
		ofsetX = 30 * (Level - 1);
	}
	switch (color)
	{
	case Red:
		switch (Level)
		{
		case 1:
			sprite->Draw(block[0], XMFLOAT2(pos.x - 120.0f, pos.y), 300.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		case 2:
			sprite->Draw(block[1], XMFLOAT2(pos.x - 120.0f + ofsetX, pos.y - 30.0f + ofsetY), 300.0f, 60.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f));
			break;
		case 3:
			sprite->Draw(block[2], XMFLOAT2(pos.x - 120.0f + ofsetX, pos.y - 60.0f + ofsetY), 300.0f, 90.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.4f, 0.4f, 1.0f));
			break;
		}
		break;
	case Yellow:
		switch (Level)
		{
		case 1:
			sprite->Draw(block[0], XMFLOAT2(pos.x - 120.0f, pos.y), 300.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
			break;
		case 2:
			sprite->Draw(block[1], XMFLOAT2(pos.x - 120.0f + ofsetX, pos.y - 30.0f + ofsetY), 300.0f, 60.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.2f, 1.0f));
			break;
		case 3:
			sprite->Draw(block[2], XMFLOAT2(pos.x - 120.0f + ofsetX, pos.y - 60.0f + ofsetY), 300.0f, 90.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.4f, 1.0f));
			break;
		}
		break;
	case Blue:
		switch (Level)
		{
		case 1:
			sprite->Draw(block[0], XMFLOAT2(pos.x - 120.0f, pos.y), 300.0f, 30.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
			break;
		case 2:
			sprite->Draw(block[1], XMFLOAT2(pos.x - 120.0f + ofsetX, pos.y - 30.0f + ofsetY), 300.0f, 60.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.2f, 0.2f, 1.0f, 1.0f));
			break;
		case 3:
			sprite->Draw(block[2], XMFLOAT2(pos.x - 120.0f + ofsetX, pos.y - 60.0f + ofsetY), 300.0f, 90.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.4f, 0.4f, 1.0f, 1.0f));
			break;
		}
		break;
	}
}

void ColorBlock::GetSpriteParent(Sprite::SpriteData *parent)
{
	assert(parent);
	block[0].parent = parent;
	block[1].parent = parent;
	block[2].parent = parent;
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
		for (int i = 0; i < 3; i++)
		{
			block[i].rotation += 90.0f;
		}
		break;
	case Right:
		pos.x = j * blockSize + 300;
		pos.y = i * blockSize - 270;
		for (int i = 0; i < 3; i++)
		{
			block[i].rotation += 90.0f;
		}
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

int ColorBlock::GetLevel()
{
	return Level;
}

void ColorBlock::LevelUP(int i)
{
	switch (i)
	{
	case 2:
		Level = 2;
		break;
	case 3:
		Level = 3;
		break;
	}
}
