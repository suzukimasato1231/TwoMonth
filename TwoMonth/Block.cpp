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
			{//ブロックの台部分
				mapUP[j][i] = 1;
				mapDown[j][i] = 1;
				mapLeft[j][i] = 1;
				mapRight[j][i] = 1;
			}
			else
			{
				mapUP[j][i] = 0;
				mapDown[j][i] = 0;
				mapLeft[j][i] = 0;
				mapRight[j][i] = 0;
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
	for (int i = 0; i < colorBlock.size(); i++)
	{//動かせるブロックがあるかどうか
		if (colorBlock[i]->GetFlag() == true)
		{
			pushFlag = false;
		}
	}//無かったらブロックを追加
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
			if (input->KeybordTrigger(DIK_LEFT))
			{
				colorBlock[i]->LeftMove();
			}
			if (input->KeybordTrigger(DIK_RIGHT))
			{
				colorBlock[i]->RightMove();
			}
		}
	}
}

void Block::ColBlock(Sprite::SpriteData *table, XMFLOAT2 tablePos, int direction)
{
	if (colorBlock.size() != 0)
	{
		XMFLOAT2 TablePos = { tablePos.x - 300 / 2,tablePos.y - 300 / 2 };
		for (int i = 0; i < mapNum; i++)
		{
			for (int j = 0; j < mapNum; j++)
			{
				switch (direction)
				{
				case UP:
					if (mapUP[j][i] == 1)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + 30 * i,TablePos.y - 30 * j };

						bool isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), 30, 30,
							mapChipPos, 30.0f, 30.0f);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit)
						{

							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction);
							mapUP[j + 1][i] = 1;

						}

					}
					break;
				case Down:
					if (mapDown[j][i] == 1)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + 30 * i,TablePos.y - 30 * j };

						bool isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), 30, 30,
							mapChipPos, 30.0f, 30.0f);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit)
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction);
							mapDown[j + 1][i] = 1;
						}
					}
					break;
				case Left:
					if (mapLeft[j][i] == 1)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + 30 * i,TablePos.y - 30 * j };

						bool isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), 30, 30,
							mapChipPos, 30.0f, 30.0f);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit)
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction);
							mapLeft[j + 1][i] = 1;
						}
					}
					break;
				case Right:
					if (mapRight[j][i] == 1)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + 30 * i,TablePos.y - 30 * j };

						bool isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), 30, 30,
							mapChipPos, 30.0f, 30.0f);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit)
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction);
							mapRight[j + 1][i] = 1;
						}
					}
					break;
				}
			}
		}
	}
}

void Block::Damege()
{
	DamegeFlag = false;
	for (int i = 0; i < mapNum; i++)
	{
		for (int j = 1; j < mapNum; j++)
		{
			if (mapUP[j][i] == 1 && mapDown[j][mapNum - i - 1] == 1)
			{
				DamegeFlag = true;
				mapUP[j][i] = 0;
				mapDown[j][mapNum - i - 1] = 0;
				//該当するブロックを削除
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == UP)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().x == mapNum - i - 1 && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
			}

			if (mapLeft[j][i] == 1 && mapRight[j][mapNum - i - 1] == 1)
			{
				DamegeFlag = true;
				mapLeft[j][i] = 0;
				mapRight[j][mapNum - i - 1] = 0;
				//該当するブロックを削除
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Left)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().x == mapNum - i - 1 && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
			}
		}
	}
}

bool Block::GetDameFlag()
{
	return DamegeFlag;
}


