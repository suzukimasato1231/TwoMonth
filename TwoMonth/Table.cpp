#include "Table.h"


Table::Table()
{
}

Table::~Table()
{
}

void Table::Init(Input *input, Sprite *sprite, Object *object)
{
	assert(input);
	this->input = input;
	assert(sprite);
	this->sprite = sprite;
	assert(object);
	this->object = object;

	//table = sprite->SpriteCreate(L"Resources/texture2.jpg");

	graph = object->LoadTexture(L"Resources/table.png");
	table = object->CreateSquare(300.0f, 300.0f, 100.0f);

}


void Table::MainInit()
{
	Status = UP;
	//回転してるかどうか
	rotationFlag = false;
	rotationMemory = 0;
	rotation.z = 0;
}

void Table::Update()
{
	//左回転
	if ((input->KeybordTrigger(DIK_A) || input->KeybordTrigger(DIK_LEFT) || input->ControllerUp(ButtonLB)) && rotationFlag == false)
	{
		rotationMemory = rotation.z - 90.0f;
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
	if ((input->KeybordTrigger(DIK_D) || input->KeybordTrigger(DIK_RIGHT) || input->ControllerUp(ButtonRB)) && rotationFlag == false)
	{
		rotationMemory = rotation.z + 90.0f;
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
	if ((input->KeybordTrigger(DIK_S) || input->KeybordTrigger(DIK_DOWN) || input->KeybordTrigger(DIK_UP) || input->KeybordTrigger(DIK_W) || input->ControllerUp(ButtonY)) && rotationFlag == false)
	{
		rotationMemory = rotation.z + 180.0f;
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
	if (rotationFlag == true && rotationMemory > rotation.z)
	{
		rotation.z += 5;
		if (rotationMemory == rotation.z)
		{
			rotationFlag = false;
			if (rotation.z == 360)
			{//オーバーフロー対策
				rotation.z -= 360.0f;
			}
		}
	}//左回り
	if (rotationFlag == true && rotationMemory < rotation.z)
	{
		rotation.z -= 5;
		if (rotationMemory == rotation.z)
		{
			rotationFlag = false;
			if (rotation.z == -360)
			{//オーバーフロー対策
				rotation.z += 360.0f;
			}
		}
	}

	ShakeStart(10.0f, 10);

	ShakeUpdate();
}

void Table::Draw()
{
	object->Draw(table, XMFLOAT3(pos.x + shakeX, pos.y + shakeY, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), rotation,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), graph);
}

XMFLOAT3 Table::GetPos()
{
	return pos;
}

int Table::GetStatus()
{
	return Status;
}



void Table::ShakeUpdate()
{
	//シェイク初期化
	shakeX = 0, shakeY = 0;
	//シェイクが続く時間
	if (shakeTime > 0)
	{
		shakeX = (rand() % shakeString - shakeString / 2) * shkeStringTime;
		shakeY = (rand() % shakeString - shakeString / 2) * shkeStringTime;
		shakeTime -= 1;
		shkeStringTime -= 0.1f;
	}
}

void Table::ShakeStart(float shakeTime, int shakeString)
{
	if (shakeFlag == true)
	{
		//シェイクする時間
		this->shakeTime = shakeTime;
		//シェイクの強さ
		this->shakeString = shakeString;
		//減衰
		shkeStringTime = shakeTime / 10;
		shakeFlag = false;
	}
}

bool Table::ShakeGet(bool shakeFlag)
{
	return this->shakeFlag = shakeFlag;
}

bool Table::GetShakeFlag()
{
	return shakeFlag;
}

int Table::GetShakeTime()
{
	return shakeTime;
}
