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

	//table = sprite->SpriteCreate(L"Resources/texture2.jpg");
	table = sprite->SpriteCreate(L"Resources/table.png");
}


void Table::MainInit()
{
	Status = UP;
	//��]���Ă邩�ǂ���
	rotationFlag = false;
	rotationMemory = 0;
	table.rotation = 0;
}

void Table::Update()
{
	//����]
	if ((input->KeybordTrigger(DIK_A) || input->KeybordTrigger(DIK_LEFT) || input->ControllerUp(ButtonLB)) && rotationFlag == false)
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
	//�E��]
	if ((input->KeybordTrigger(DIK_D) || input->KeybordTrigger(DIK_RIGHT) || input->ControllerUp(ButtonRB)) && rotationFlag == false)
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
	//����]
	if ((input->KeybordTrigger(DIK_S) || input->KeybordTrigger(DIK_DOWN) || input->KeybordTrigger(DIK_UP) || input->KeybordTrigger(DIK_W) || input->ControllerUp(ButtonY)) && rotationFlag == false)
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
	//��]��
	//�E���
	if (rotationFlag == true && rotationMemory > table.rotation)
	{
		table.rotation += 5;
		if (rotationMemory == table.rotation)
		{
			rotationFlag = false;
			if (table.rotation == 360)
			{//�I�[�o�[�t���[�΍�
				table.rotation -= 360.0f;
			}
		}
	}//�����
	if (rotationFlag == true && rotationMemory < table.rotation)
	{
		table.rotation -= 5;
		if (rotationMemory == table.rotation)
		{
			rotationFlag = false;
			if (table.rotation == -360)
			{//�I�[�o�[�t���[�΍�
				table.rotation += 360.0f;
			}
		}
	}

	ShakeStart(10.0f, 10);

	ShakeUpdate();
}

void Table::Draw()
{
	sprite->Draw(table, XMFLOAT2(pos.x + shakeX, pos.y + shakeY), width, height, XMFLOAT2(0.5f, 0.5f));
}

XMFLOAT2 Table::GetPos()
{
	return pos;
}

int Table::GetStatus()
{
	return Status;
}



void Table::ShakeUpdate()
{
	//�V�F�C�N������
	shakeX = 0, shakeY = 0;
	//�V�F�C�N����������
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
		//�V�F�C�N���鎞��
		this->shakeTime = shakeTime;
		//�V�F�C�N�̋���
		this->shakeString = shakeString;
		//����
		shkeStringTime = shakeTime / 10;
		shakeFlag = false;
	}
}

bool Table::ShakeGet(bool shakeFlag)
{
	return this->shakeFlag = shakeFlag;
}
