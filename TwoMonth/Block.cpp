#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
	for (int i = (int)colorBlock.size() - 1; i >= 0; i--)
	{
		delete colorBlock[i];
		colorBlock.erase(colorBlock.begin() + i);
	}
}

void Block::Init(Input *input, Sprite *sprite)
{
	assert(input);
	this->input = input;
	assert(sprite);
	this->sprite = sprite;

	block = sprite->SpriteCreate(L"Resources/white.png");

	for (int i = 0; i < mapNum; i++)
	{
		for (int j = 0; j < mapNum; j++)
		{
			if (j == 0)
			{//�u���b�N�̑䕔��
				mapUP[j] = Foundation;
				mapDown[j] = Foundation;
				mapLeft[j] = Foundation;
				mapRight[j] = Foundation;
			}
			else
			{
				mapUP[j] = 0;
				mapDown[j] = 0;
				mapLeft[j] = 0;
				mapRight[j] = 0;
			}
		}
	}
}

void Block::Update()
{
	AddBlock();

	MoveBlock();

	Damege();
}

void Block::Draw()
{
	for (int i = 0; i < colorBlock.size(); i++)
	{
		colorBlock[i]->Draw();
	}
}


void Block::AddBlock()
{
	int pushFlag = true;
	addFlag = true;
	for (int i = 0; i < colorBlock.size(); i++)
	{//��������u���b�N�����邩�ǂ���
		if (colorBlock[i]->GetFlag() == true)
		{
			addFlag = false;
			pushFlag = false;
		}
	}//����������u���b�N��ǉ�
	if (pushFlag == true)
	{
		colorBlock.push_back(new ColorBlock);
		colorBlock[colorBlock.size() - 1]->Init(block, sprite);
	}
}

void Block::MoveBlock()
{
	for (int i = 0; i < colorBlock.size(); i++)
	{
		if (colorBlock[i]->GetFlag() == true)
		{
			colorBlock[i]->Update();
		}
	}
}


void Block::ColBlock(Sprite::SpriteData *table, XMFLOAT2 tablePos, int direction)
{
	if (colorBlock.size() != 0)
	{
		XMFLOAT2 TablePos = { tablePos.x - 30 * 5,tablePos.y - 30 * 5 };
		for (int j = 0; j < mapNum; j++)
		{
			switch (direction)
			{
			case UP:
				if (mapUP[j] > 0)
				{
					XMFLOAT2 mapChipPos{ TablePos.x + blockSize * (blockX - 1),TablePos.y - blockSize * j };

					int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
						mapChipPos, 30.0f, 30.0f);
					if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
					{//��̏�ł̍��W�������
						colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
						colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
						mapUP[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
					}
				}
				break;
			case Down:
				if (mapDown[j] > 0)
				{
					XMFLOAT2 mapChipPos{ TablePos.x + blockSize * (blockX - 1),TablePos.y - blockSize * j };

					int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
						mapChipPos, blockSize, blockSize);
					if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
					{//��̏�ł̍��W�������
						colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
						colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
						mapDown[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
					}
				}
				break;
			case Left:
				if (mapLeft[j] > 0)
				{
					XMFLOAT2 mapChipPos{ TablePos.x + blockSize * (blockX - 1),TablePos.y - blockSize * j };

					int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
						mapChipPos, blockSize, blockSize);
					if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
					{//��̏�ł̍��W�������
						colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
						colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
						mapLeft[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
					}
				}
				break;
			case Right:
				if (mapRight[j] > 0)
				{
					XMFLOAT2 mapChipPos{ TablePos.x + blockSize * (blockX - 1),TablePos.y - blockSize * j };

					int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
						mapChipPos, blockSize, blockSize);
					if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
					{//��̏�ł̍��W�������
						colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
						colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
						mapRight[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
					}
				}
				break;
			}
		}
	}
}

void Block::Damege()
{
	DamegeFlag = false;
	for (int j = 1; j < mapNum; j++)
	{//����ł��邩�ǂ���
		if (mapUP[j] > 0 && mapDown[j] > 0)
		{
			DamegeFlag = true;
			mapUP[j] = 0;
			mapDown[j] = 0;
			//�Y������u���b�N���폜
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == UP)
				{
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
				{
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
		}
		//����ł��邩�ǂ���
		if (mapLeft[j] > 0 && mapRight[j] > 0)
		{
			DamegeFlag = true;
			mapLeft[j] = 0;
			mapRight[j] = 0;
			//�Y������u���b�N���폜
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Left)
				{
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
				{
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
		}
		//�u���b�N�����炷
		BlockShift(blockX, j);
	}
}

void Block::DeleteBlock()
{
	for (int n = 0; n < colorBlock.size(); n++)
	{
		delete colorBlock[n];
		colorBlock.erase(colorBlock.begin() + n);
	}
}

void Block::BlockShift(int i, int j)
{
	//���Ƀu���b�N�����������炸���
	if (mapUP[j] > 0 && mapUP[j - 1] == 0)
	{
		mapUP[j - 1] = mapUP[j];
		mapUP[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == UP)
			{//���W�X�V
				colorBlock[n]->ShiftPos(blockX, j - 2, UP, blockSize);
			}
		}
	}
	//���Ƀu���b�N�����������炸���
	if (mapLeft[j] > 0 && mapLeft[j - 1] == 0)
	{
		mapLeft[j - 1] = mapLeft[j];
		mapLeft[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Left)
			{//���W�X�V
				colorBlock[n]->ShiftPos(blockX, j - 2, Left, blockSize);
			}
		}
	}
	//���Ƀu���b�N�����������炸���
	if (mapDown[j] > 0 && mapDown[j - 1] == 0)
	{
		mapDown[j - 1] = mapDown[j];
		mapDown[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
			{//���W�X�V
				colorBlock[n]->ShiftPos(blockX, j - 2, Down, blockSize);
			}
		}
	}
	//���Ƀu���b�N�����������炸���
	if (mapRight[j] > 0 && mapRight[j - 1] == 0)
	{
		mapRight[j - 1] = mapRight[j];
		mapRight[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
			{//���W�X�V
				colorBlock[n]->ShiftPos(blockX, j - 2, Right, blockSize);
			}
		}
	}
}

bool Block::GetDameFlag()
{
	return DamegeFlag;
}

bool Block::GetAddFlag()
{
	return addFlag;
}


