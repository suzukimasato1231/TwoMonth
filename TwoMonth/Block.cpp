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

void Block::Update(Sprite::SpriteData *table, int direction)
{
	AddBlock();

	MoveBlock(table, direction);

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

void Block::MoveBlock(Sprite::SpriteData *table, int direction)
{
	for (int i = 0; i < colorBlock.size(); i++)
	{
		if (colorBlock[i]->GetFlag() == true)
		{
			colorBlock[i]->Update();
			//ハードドロップ
			HardDrop(table, direction);
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
					{//台の上での座標をいれる
						if (mapUP[j + 1] > 0)
						{
							BlockSetRot(table, direction);
						}
						else
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
							mapUP[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
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
					{//台の上での座標をいれる
						if (mapDown[j + 1] > 0)
						{
							BlockSetRot(table, direction);
						}
						else
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
							mapDown[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
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
					{//台の上での座標をいれる
						if (mapLeft[j + 1] > 0)
						{
							BlockSetRot(table, direction);
						}
						else
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
							mapLeft[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
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
					{//台の上での座標をいれる
						if (mapRight[j + 1] > 0)
						{
							BlockSetRot(table, direction);
						}
						else
						{
							colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
							colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j, direction, blockSize);
							mapRight[j + 1] = colorBlock[colorBlock.size() - 1]->GetColor();
						}
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
	{//挟んでいるかどうか
		if (mapUP[j] > 0 && mapDown[j] > 0)
		{
			sandFlag = true;
			sandDelay++;
			if (sandDelay > 120 && sandFlag == true)
			{
				mapUP[j] = 0;
				mapDown[j] = 0;
				//該当するブロックを削除
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
				DamegeFlag = true;
				sandFlag = 0;
				addFlag = true;
				sandDelay = 0;
			}
		}
		//挟んでいるかどうか
		if (mapLeft[j] > 0 && mapRight[j] > 0)
		{
			sandFlag = true;
			sandDelay++;
			if (sandDelay > 120 && sandFlag == true)
			{
				mapLeft[j] = 0;
				mapRight[j] = 0;
				//該当するブロックを削除
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
				DamegeFlag = true;
				sandFlag = 0;
				addFlag = true;
				sandDelay = 0;
			}
		}
		//ブロックをずらす
		BlockShift(blockX, j);
	}
}

void Block::DeleteBlock()
{
	for (int i = (int)colorBlock.size() - 1; i >= 0; i--)
	{
		delete colorBlock[i];
		colorBlock.erase(colorBlock.begin() + i);
	}

	for (int i = 0; i < mapNum; i++)
	{
		for (int j = 0; j < mapNum; j++)
		{
			if (j == 0)
			{//ブロックの台部分
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

void Block::BlockShift(int i, int j)
{
	//下にブロックが無かったらずれる
	if (mapUP[j] > 0 && mapUP[j - 1] == 0)
	{
		mapUP[j - 1] = mapUP[j];
		mapUP[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == UP)
			{//座標更新
				colorBlock[n]->ShiftPos(blockX, j - 2, UP, blockSize);
			}
		}
	}
	//下にブロックが無かったらずれる
	if (mapLeft[j] > 0 && mapLeft[j - 1] == 0)
	{
		mapLeft[j - 1] = mapLeft[j];
		mapLeft[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Left)
			{//座標更新
				colorBlock[n]->ShiftPos(blockX, j - 2, Left, blockSize);
			}
		}
	}
	//下にブロックが無かったらずれる
	if (mapDown[j] > 0 && mapDown[j - 1] == 0)
	{
		mapDown[j - 1] = mapDown[j];
		mapDown[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
			{//座標更新
				colorBlock[n]->ShiftPos(blockX, j - 2, Down, blockSize);
			}
		}
	}
	//下にブロックが無かったらずれる
	if (mapRight[j] > 0 && mapRight[j - 1] == 0)
	{
		mapRight[j - 1] = mapRight[j];
		mapRight[j] = 0;
		for (int n = 0; n < colorBlock.size(); n++)
		{
			if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
			{//座標更新
				colorBlock[n]->ShiftPos(blockX, j - 2, Right, blockSize);
			}
		}
	}
}
void Block::HardDrop(Sprite::SpriteData *table, int direction)
{
	if (input->KeybordTrigger(DIK_SPACE))
	{
		for (int j = 1; j < mapNum; j++)
		{
			bool breakFlag = false;
			switch (direction)
			{
			case UP:
				if (mapUP[j] == 0)
				{//空いてるところに設置
					colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
					colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j - 1, direction, blockSize);
					mapUP[j] = colorBlock[colorBlock.size() - 1]->GetColor();
					breakFlag = true;
				}
				break;
			case Down:
				if (mapDown[j] == 0)
				{//空いてるところに設置
					colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
					colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j - 1, direction, blockSize);
					mapDown[j] = colorBlock[colorBlock.size() - 1]->GetColor();
					breakFlag = true;
				}
				break;
			case Left:
				if (mapLeft[j] == 0)
				{//空いてるところに設置
					colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
					colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j - 1, direction, blockSize);
					mapLeft[j] = colorBlock[colorBlock.size() - 1]->GetColor();
					breakFlag = true;
				}
				break;
			case Right:
				if (mapRight[j] == 0)
				{//空いてるところに設置
					colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
					colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), j - 1, direction, blockSize);
					mapRight[j] = colorBlock[colorBlock.size() - 1]->GetColor();
					breakFlag = true;
				}
				break;
			}
			//見つけたら抜ける
			if (breakFlag == true)
			{
				break;
			}
		}
	}
}

void Block::BlockSetRot(Sprite::SpriteData *table, int direction)
{
	switch (direction)
	{
	case UP:
		for (int i = 1; i < mapNum; i++)
		{
			if (mapUP[i] == 0)
			{
				colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
				colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), i - 1, direction, blockSize);
				mapUP[i] = colorBlock[colorBlock.size() - 1]->GetColor();
				break;
			}
		}
		break;
	case Down:
		for (int i = 1; i < mapNum; i++)
		{
			if (mapDown[i] == 0)
			{
				colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
				colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), i - 1, direction, blockSize);
				mapDown[i] = colorBlock[colorBlock.size() - 1]->GetColor();
				break;
			}
		}
		break;
	case Left:
		for (int i = 1; i < mapNum; i++)
		{
			if (mapLeft[i] == 0)
			{
				colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
				colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), i - 1, direction, blockSize);
				mapLeft[i] = colorBlock[colorBlock.size() - 1]->GetColor();
				break;
			}
		}
		break;
	case Right:
		for (int i = 1; i < mapNum; i++)
		{
			if (mapRight[i] == 0)
			{
				colorBlock[colorBlock.size() - 1]->GetSpriteParent(table);
				colorBlock[colorBlock.size() - 1]->Pos((blockX - 1), i - 1, direction, blockSize);
				mapRight[i] = colorBlock[colorBlock.size() - 1]->GetColor();
				break;
			}
		}
		break;
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

int Block::GetSandDelay()
{
	return sandDelay;
}

void Block::SetSandDelay(int count)
{
	sandDelay = count;
}

