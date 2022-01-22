#include "ColorBlock.h"

ColorBlock::ColorBlock() {}

ColorBlock::~ColorBlock() {}

void ColorBlock::Init(Object::ObjectData block, Object::ObjectData block2, Object::ObjectData block3,
	Object::ObjectData block4, Object::ObjectData block5, Object::ObjectData block6,
	Object::ObjectData block7, Object::ObjectData block8, Object::ObjectData block9, Object *object, int color, int redGraph, int yellowGraph, int blueGraph)
{
	this->block[0] = block;
	this->block[1] = block2;
	this->block[2] = block3;
	this->block[3] = block4;
	this->block[4] = block5;
	this->block[5] = block6;
	this->block[6] = block7;
	this->block[7] = block8;
	this->block[8] = block9;
	assert(object);
	this->object = object;
	//色の画像をコピー
	this->redGraph = redGraph;
	this->yellowGraph = yellowGraph;
	this->blueGraph = blueGraph;
	this->color = color;
}

void ColorBlock::Update()
{
	oldPos = pos;
	if (Flag == true)
	{
		//pos.y += 1.0f;
		pos.y -= 0.1f;
	}
}

void ColorBlock::Draw()
{
	int ofsetY = 0, ofsetX = 0;
	if (Status == Down)
	{
		ofsetY = -60 * (Level - 1) + 30 * (Level - 1);
	}
	if (Status == Left)
	{
		ofsetY = -30 * (Level - 1) + 15 * (Level - 1);
		ofsetX = 30 * (Level - 1) - 15 * (Level - 1);
	}
	if (Status == Right)
	{
		ofsetY = -30 * (Level - 1) + 15 * (Level - 1);
		ofsetX = -30 * (Level - 1) + 15 * (Level - 1);
	}
	switch (color)
	{
	case Red:
		switch (Level)
		{
		case 1:
			object->Draw(block[0], XMFLOAT3(pos.x, pos.y, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), redGraph);
			break;
		case 2:
			object->Draw(block[1], XMFLOAT3(pos.x + ofsetX, pos.y + ofsetY + 15.0f, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), redGraph);
			break;
		case 3:
			object->Draw(block[2], XMFLOAT3(pos.x + ofsetX, pos.y + ofsetY + 30.0f, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), redGraph);
			break;
		}
		break;
	case Yellow:
		switch (Level)
		{
		case 1:
			object->Draw(block[3], XMFLOAT3(pos.x, pos.y, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), yellowGraph);
			break;
		case 2:
			object->Draw(block[4], XMFLOAT3(pos.x + ofsetX, pos.y + ofsetY + 15.0f, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), yellowGraph);
			break;
		case 3:
			object->Draw(block[5], XMFLOAT3(pos.x + ofsetX, pos.y + ofsetY + 30.0f, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), yellowGraph);
			break;
		}
		break;
	case Blue:
		switch (Level)
		{
		case 1:
			object->Draw(block[6], XMFLOAT3(pos.x, pos.y, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), blueGraph);
			break;
		case 2:
			object->Draw(block[7], XMFLOAT3(pos.x + ofsetX, pos.y + ofsetY + 15.0f, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), blueGraph);
			break;
		case 3:
			object->Draw(block[8], XMFLOAT3(pos.x + ofsetX, pos.y + ofsetY + 30.0f, -40.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				rotation, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), blueGraph);
			break;
		}
		break;
	}
}

void ColorBlock::GetSpriteParent(Object::ObjectData *parent)
{
	assert(parent);
	block[0].parent = parent;
	block[1].parent = parent;
	block[2].parent = parent;
	block[3].parent = parent;
	block[4].parent = parent;
	block[5].parent = parent;
	block[6].parent = parent;
	block[7].parent = parent;
	block[8].parent = parent;
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

void ColorBlock::SpeedUpdate()
{
	if (Flag == true)
	{
		pos.y -= 10.0f;
	}
}

XMFLOAT3 ColorBlock::GetPos()
{
	return pos;
}

XMFLOAT3 ColorBlock::GetoldPos()
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
		pos.x = i * blockSize - 120;
		pos.y = 135 + blockSize + j * blockSize;
		break;
	case Down:
		pos.x = -i * blockSize + 150 - blockSize;
		pos.y = -165 - j * blockSize;
		for (int i = 0; i < 9; i++)
		{
			rotation.z += 180.0f;
		}
		break;
	case Left:
		pos.x = j * blockSize - blockSize + 195;
		pos.y = -i * blockSize + blockSize + 90;
		for (int i = 0; i < 9; i++)
		{
			rotation.z -= 90.0f;
		}
		break;
	case Right:
		pos.x = -j * blockSize - 165;
		pos.y = -i * blockSize + 120;
		for (int i = 0; i < 9; i++)
		{
			rotation.z += 90.0f;
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
		pos.x = i * blockSize - 150;
		pos.y = 135 + blockSize + j * blockSize;
		break;
	case Down:
		pos.x = -i * blockSize + 180 - blockSize;
		pos.y = -165 - j * blockSize;
		break;
	case Left:
		pos.x = j * blockSize - blockSize + 195;
		pos.y = -i * blockSize + blockSize + 120;
		break;
	case Right:
		pos.x = -j * blockSize - 165;
		pos.y = -i * blockSize + 150;
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
bool ColorBlock::GetDeleteFlag()
{
	return DeleteFlag;
}

void ColorBlock::BreakFlagTRUE()
{
	blockBreakFlag = true;
}

void ColorBlock::Sandwich()
{
	if (blockBreakFlag == true)
	{
		switch (Status)
		{
		case UP:
			pos.y -= 7.5f;
			break;
		case Down:
			pos.y += 7.5f;
			break;
		case Left:
			pos.x -= 7.5f;
			break;
		case Right:
			pos.x += 7.5f;
			break;
		}
		time--;
		if (time <= 0)
		{
			DeleteFlag = true;
		}
	}
}

bool ColorBlock::GetBreakFlag()
{
	return blockBreakFlag;
}
