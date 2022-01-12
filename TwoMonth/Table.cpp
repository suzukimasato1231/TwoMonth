#include "Table.h"

Table::Table()
{
}

Table::~Table()
{
}

void Table::Init(Input *input, Sprite *sprite)
{
	assert(input);
	this->input = input;
	assert(sprite);
	this->sprite = sprite;

	table = sprite->SpriteCreate(L"Resources/texture2.jpg");
}

void Table::Update()
{
	//左回転
	if (input->KeybordTrigger(DIK_A) && rotationFlag == false)
	{
		rotationMemory = table.rotation - 90.0f;
		rotationFlag = true;
		switch (Status)
		{
		case UP:
			Status = Right;
			break;
		case Left:
			Status = UP;
			break;
		case Down:
			Status = Left;
			break;
		case Right:
			Status = Down;
			break;
		}
	}
	//右回転
	if (input->KeybordTrigger(DIK_D) && rotationFlag == false)
	{
		rotationMemory = table.rotation + 90.0f;
		rotationFlag = true;
		switch (Status)
		{
		case UP:
			Status = Left;
			break;
		case Left:
			Status = Down;
			break;
		case Down:
			Status = Right;
			break;
		case Right:
			Status = UP;
			break;
		}
	}
	//半回転
	if (input->KeybordTrigger(DIK_S) && rotationFlag == false)
	{
		rotationMemory = table.rotation + 180.0f;
		rotationFlag = true;
		switch (Status)
		{
		case UP:
			Status = Down;
			break;
		case Left:
			Status = Right;
			break;
		case Down:
			Status = UP;
			break;
		case Right:
			Status = Left;
			break;
		}
	}
	//回転中
	//右回り
	if (rotationFlag == true && rotationMemory > table.rotation)
	{
		table.rotation += 5;
		if (rotationMemory == table.rotation)
		{
			rotationFlag = false;
			if (table.rotation == 360)
			{//オーバーフロー対策
				table.rotation -= 360.0f;
			}
		}
	}//左回り
	if (rotationFlag == true && rotationMemory < table.rotation)
	{
		table.rotation -= 5;
		if (rotationMemory == table.rotation)
		{
			rotationFlag = false;
			if (table.rotation == -360)
			{//オーバーフロー対策
				table.rotation += 360.0f;
			}
		}
	}
}

void Table::Draw()
{
	sprite->Draw(table, pos, width, height, XMFLOAT2(0.5f, 0.5f));
}

XMFLOAT2 Table::GetPos()
{
	return pos;
}

int Table::GetStatus()
{
	return Status;
}


