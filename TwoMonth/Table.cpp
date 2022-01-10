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
	//‰ñ“]
	if (input->KeybordTrigger(DIK_A))
	{
		table.rotation -= 90;
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
	if (input->KeybordTrigger(DIK_D))
	{
		table.rotation += 90;
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


