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
	addFlag = true;
	for (int i = 0; i < colorBlock.size(); i++)
	{//動かせるブロックがあるかどうか
		if (colorBlock[i]->GetFlag() == true)
		{
			addFlag = false;
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
		}
	}
}


void Block::ColBlock(Sprite::SpriteData *table, XMFLOAT2 tablePos, int direction)
{
	if (colorBlock.size() != 0)
	{
		XMFLOAT2 TablePos = { tablePos.x - blockSize * mapNum / 2,tablePos.y - blockSize * mapNum / 2 };
		for (int i = 0; i < mapNum; i++)
		{
			for (int j = 0; j < mapNum; j++)
			{
				switch (direction)
				{
				case UP:
					if (mapUP[j][i] > 0)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + blockSize * i,TablePos.y - blockSize * j };

						int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
							mapChipPos, 30.0f, 30.0f);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
						{//台の上での座標をいれる
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction, blockSize);
							mapUP[j + 1][i] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
					}
					break;
				case Down:
					if (mapDown[j][i] > 0)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + blockSize * i,TablePos.y - blockSize * j };

						int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
							mapChipPos, blockSize, blockSize);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
						{//台の上での座標をいれる
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction, blockSize);
							mapDown[j + 1][i] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
					}
					break;
				case Left:
					if (mapLeft[j][i] > 0)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + blockSize * i,TablePos.y - blockSize * j };

						int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
							mapChipPos, blockSize, blockSize);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
						{//台の上での座標をいれる
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction, blockSize);
							mapLeft[j + 1][i] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
					}
					break;
				case Right:
					if (mapRight[j][i] > 0)
					{
						XMFLOAT2 mapChipPos{ TablePos.x + blockSize * i,TablePos.y - blockSize * j };

						int isHit = Collision::MapChipCollision(colorBlock[colorBlock.size() - 1]->GetPos(), colorBlock[colorBlock.size() - 1]->GetoldPos(), 30, 30,
							mapChipPos, blockSize, blockSize);
						if (colorBlock[colorBlock.size() - 1]->GetFlag() && isHit == 1)
						{//台の上での座標をいれる
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos(i, j, direction, blockSize);
							mapRight[j + 1][i] = colorBlock[colorBlock.size() - 1]->GetColor();
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
		{//挟んでいるかどうか
			if (mapUP[j][i] > 0 && mapDown[j][i] > 0)
			{
				DamegeFlag = true;
				mapUP[j][i] = 0;
				mapDown[j][i] = 0;
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
					if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
			}
			//挟んでいるかどうか
			if (mapLeft[j][i] > 0 && mapRight[j][i] > 0)
			{
				DamegeFlag = true;
				mapLeft[j][i] = 0;
				mapRight[j][i] = 0;
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
					if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
			}
			//ブロックをずらす
			BlockShift(i, j);
		}
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
	//下にブロックが無かったらずれる
	if (mapUP[j][i] > 0 && mapUP[j - 1][i] == 0)
	{
		mapUP[j - 1][i] = mapUP[j][i];
		mapUP[j][i] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == UP)
			{//座標更新
				colorBlock[n]->ShiftPos(i, j - 2, UP, blockSize);
			}
		}
	}
	//下にブロックが無かったらずれる
	if (mapLeft[j][i] > 0 && mapLeft[j - 1][i] == 0)
	{
		mapLeft[j - 1][i] = mapLeft[j][i];
		mapLeft[j][i] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Left)
			{//座標更新
				colorBlock[n]->ShiftPos(i, j - 2, Left, blockSize);
			}
		}
	}
	//下にブロックが無かったらずれる
	if (mapDown[j][i] > 0 && mapDown[j - 1][i] == 0)
	{
		mapDown[j - 1][i] = mapDown[j][i];
		mapDown[j][i] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
			{//座標更新
				colorBlock[n]->ShiftPos(i, j - 2, Down, blockSize);
			}
		}
	}
	//下にブロックが無かったらずれる
	if (mapRight[j][i] > 0 && mapRight[j - 1][i] == 0)
	{
		mapRight[j - 1][i] = mapRight[j][i];
		mapRight[j][i] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().x == i && colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
			{//座標更新
				colorBlock[n]->ShiftPos(i, j - 2, Right, blockSize);
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


