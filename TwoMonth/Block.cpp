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

	block[0] = sprite->SpriteCreate(L"Resources/white.png");

	block[1] = sprite->SpriteCreate(L"Resources/white.png");

	block[2] = sprite->SpriteCreate(L"Resources/white.png");

	nextBlock = sprite->SpriteCreate(L"Resources/nextBlock.png");
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

void Block::Update(Sprite::SpriteData *table, int direction)
{
	AddBlock(direction);

	MoveBlock(table, direction);

	BlockJoin();

	Damege();

	Overflow();

	CountGamaeOverTime();
}

void Block::Draw()
{
	for (int i = 0; i < colorBlock.size(); i++)
	{
		colorBlock[i]->Draw();
	}
	//次のブロックの表示
	sprite->Draw(nextBlock, XMFLOAT2(1400.0f, 0.0f), 500.0f, 200.0f);
	switch (memoryColor)
	{
	case Red:
		sprite->Draw(block[0], XMFLOAT2(1500.0f, 150.0f), 300.0f, 30.0f,
			XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case Yellow:
		sprite->Draw(block[0], XMFLOAT2(1500.0f, 150.0f), 300.0f, 30.0f,
			XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Blue:
		sprite->Draw(block[0], XMFLOAT2(1500.0f, 150.0f), 300.0f, 30.0f,
			XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	}
}


void Block::AddBlock(int direction)
{
	int pushFlag = true;
	const int mapY = 12;//おけなくなるブロックの高さ
	addFlag = true;
	for (int i = 0; i < colorBlock.size(); i++)
	{//動かせるブロックがあるかどうか
		if (colorBlock[i]->GetFlag() == true)
		{
			addFlag = false;
			pushFlag = false;
			//おけなくなるブロックの高さまでいったらブロックを消す
			if ((direction == UP && mapUP[mapY] > 0) || (direction == Down && mapDown[mapY] > 0) ||
				(direction == Left && mapLeft[mapY] > 0) || (direction == Right && mapRight[mapY] > 0))
			{
				memoryColor = colorBlock[i]->GetColor();//色のデータを保持
				delete colorBlock[i];
				colorBlock.erase(colorBlock.begin() + i);
			}
		}
	}//無かったらブロックを追加
	if (pushFlag == true && ((direction == UP && mapUP[mapY] == 0) || (direction == Down && mapDown[mapY] == 0) ||
		(direction == Left && mapLeft[mapY] == 0) || (direction == Right && mapRight[mapY] == 0)))
	{
		colorBlock.push_back(new ColorBlock);
		colorBlock[colorBlock.size() - 1]->Init(block[0], block[1], block[2], sprite,memoryColor);
		memoryColor = rand() % 3 + 1;//色のデータを決める
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
	checkFlag = 0;
	checkColorUp = 0;
	checkColorDown = 0;
	checkColorLeft = 0;
	checkColorRight = 0;
	for (int j = 1; j < mapNum; j++)
	{//挟んでいるかどうか
		if (mapUP[j] > 0 && mapDown[j] > 0)
		{
			sandFlag = true;
			mapUP[j] = 0;
			//該当するブロックを削除
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == UP)
				{
					LevelDelete(UP, n, j);
					checkColorUp = colorBlock[n]->GetColor();
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
			mapDown[j] = 0;
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Down)
				{
					LevelDelete(Down, n, j);
					checkColorDown = colorBlock[n]->GetColor();
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
			checkFlag = 1;
			comboCount++;
			sandDelay = 0;
		}
		//挟んでいるかどうか
		if (mapLeft[j] > 0 && mapRight[j] > 0)
		{
			sandFlag = true;
			mapLeft[j] = 0;
			//該当するブロックを削除
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Left)
				{
					LevelDelete(Left, n, j);
					checkColorLeft = colorBlock[n]->GetColor();
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
			mapRight[j] = 0;
			for (int n = 0; n < colorBlock.size(); n++)
			{
				if (colorBlock[n]->Getmap().y == j && colorBlock[n]->GetStatus() == Right)
				{
					LevelDelete(Right, n, j);
					checkColorRight = colorBlock[n]->GetColor();
					delete colorBlock[n];
					colorBlock.erase(colorBlock.begin() + n);
				}
			}
			checkFlag = 1;
			comboCount++;
			sandDelay = 0;
		}
		//ブロックをずらす
		BlockShift(blockX, j);
	}
	if (sandFlag == true) {
		sandDelay++;
	}
	if (sandDelay > 150 && sandFlag == true)
	{
		DamegeFlag = true;
		sandFlag = 0;
		addFlag = true;
		sandDelay = 0;
		comboCount = 0;
	}
}

void Block::DeleteBlock()
{
	for (int i = (int)colorBlock.size() - 1; i >= 0; i--)
	{
		delete colorBlock[i];
		colorBlock.erase(colorBlock.begin() + i);
	}

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
	if (input->KeybordTrigger(DIK_SPACE) || input->ControllerUp(ButtonA))
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


void Block::LevelDelete(int direction, int blockNum, int mapY)
{
	switch (direction)
	{
	case UP://レベルに合わせてマップチップ削除
		if (colorBlock[blockNum]->GetLevel() == 3 && mapY < mapNum - 2)
		{
			mapUP[mapY + 1] = 0;
			mapUP[mapY + 2] = 0;
		}
		if (colorBlock[blockNum]->GetLevel() == 2 && mapY < mapNum - 1)
		{
			mapUP[mapY + 1] = 0;
		}
		break;
	case Down:
		if (colorBlock[blockNum]->GetLevel() == 3 && mapY < mapNum - 2)
		{
			mapDown[mapY + 1] = 0;
			mapDown[mapY + 2] = 0;
		}
		if (colorBlock[blockNum]->GetLevel() == 2 && mapY < mapNum - 1)
		{
			mapDown[mapY + 1] = 0;
		}
		break;
	case Left:
		if (colorBlock[blockNum]->GetLevel() == 3 && mapY < mapNum - 2)
		{
			mapLeft[mapY + 1] = 0;
			mapLeft[mapY + 2] = 0;
		}
		if (colorBlock[blockNum]->GetLevel() == 2 && mapY < mapNum - 1)
		{
			mapLeft[mapY + 1] = 0;
		}
		break;
	case Right:
		if (colorBlock[blockNum]->GetLevel() == 3 && mapY < mapNum - 2)
		{
			mapRight[mapY + 1] = 0;
			mapRight[mapY + 2] = 0;
		}
		if (colorBlock[blockNum]->GetLevel() == 2 && mapY < mapNum - 1)
		{
			mapRight[mapY + 1] = 0;
		}
		break;
	}

}
void Block::BlockJoin()
{
	//上
	for (int i = 1; i < mapNum - 2; i++)
	{
		for (int color = Red; color < Foundation; color++)
		{
			//上
			//３つ
			if (mapUP[i] == color && mapUP[i + 1] == color && mapUP[i + 2] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == UP && colorBlock[n]->GetLevel() == 2)
					{
						colorBlock[n]->LevelUP(3);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 2 && colorBlock[n]->GetStatus() == UP && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}
			//2つ
			else if (mapUP[i] == color && mapUP[i + 1] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == UP && colorBlock[n]->GetLevel() == 1)
					{
						colorBlock[n]->LevelUP(2);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 1 && colorBlock[n]->GetStatus() == UP && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}
			//下
			//3つ
			if (mapDown[i] == color && mapDown[i + 1] == color && mapDown[i + 2] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == Down && colorBlock[n]->GetLevel() == 2)
					{
						colorBlock[n]->LevelUP(3);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 2 && colorBlock[n]->GetStatus() == Down && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}

			//2つ
			if (mapDown[i] == color && mapDown[i + 1] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == Down && colorBlock[n]->GetLevel() == 1)
					{
						colorBlock[n]->LevelUP(2);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 1 && colorBlock[n]->GetStatus() == Down && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}
			//右
			if (mapRight[i] == color && mapRight[i + 1] == color && mapRight[i + 2] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == Right && colorBlock[n]->GetLevel() == 2)
					{
						colorBlock[n]->LevelUP(3);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 2 && colorBlock[n]->GetStatus() == Right && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}

			//2つ
			if (mapRight[i] == color && mapRight[i + 1] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == Right && colorBlock[n]->GetLevel() == 1)
					{
						colorBlock[n]->LevelUP(2);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 1 && colorBlock[n]->GetStatus() == Right && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}
			//左
			if (mapLeft[i] == color && mapLeft[i + 1] == color && mapLeft[i + 2] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == Left && colorBlock[n]->GetLevel() == 2)
					{
						colorBlock[n]->LevelUP(3);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 2 && colorBlock[n]->GetStatus() == Left && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
						break;
					}
				}
			}

			//2つ
			if (mapLeft[i] == color && mapLeft[i + 1] == color)
			{
				bool Flag = false;
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i && colorBlock[n]->GetStatus() == Left && colorBlock[n]->GetLevel() == 1)
					{
						colorBlock[n]->LevelUP(2);
						Flag = true;
					}
				}
				for (int n = 0; n < colorBlock.size(); n++)
				{
					if (colorBlock[n]->Getmap().y == i + 1 && colorBlock[n]->GetStatus() == Left && Flag == true)
					{
						delete colorBlock[n];
						colorBlock.erase(colorBlock.begin() + n);
					}
				}
			}
		}
	}
}

void Block::CountGamaeOverTime()
{
	for (int i = UP; i < 4; i++)
	{
		if (blockOverFlag[i] == true)
		{
			end_time[i] = time(NULL);
			gameOverCount[i] = end_time[i] - start_time[i];
			//５秒経ったらゲームオーバー
			if (gameOverCount[i] > gameOverTimeMax)
			{
				gameOverFlag = true;
			}
		}
	}
}
//ブロックがあふれたかどうか
void Block::Overflow()
{
	const int mapY = 8;
	if (mapUP[mapY] > 0)
	{
		if (blockOverFlag[UP] == false)
		{
			blockOverFlag[UP] = true;
			start_time[UP] = time(NULL);
		}
	}
	else
	{
		blockOverFlag[UP] = false;
		gameOverCount[UP] = 0;

	}
	if (mapDown[mapY] > 0)
	{
		if (blockOverFlag[Down] == false)
		{
			blockOverFlag[Down] = true;
			start_time[Down] = time(NULL);
		}
	}
	else
	{
		blockOverFlag[Down] = false;
		gameOverCount[Down] = 0;
	}
	if (mapLeft[mapY] > 0)
	{
		if (blockOverFlag[Left] == false)
		{
			blockOverFlag[Left] = true;
			start_time[Left] = time(NULL);
		}
	}
	else
	{
		blockOverFlag[Left] = false;
		gameOverCount[Left] = 0;
	}
	if (mapRight[mapY] > 0)
	{
		if (blockOverFlag[Right] == false)
		{
			blockOverFlag[Right] = true;
			start_time[Right] = time(NULL);
		}
	}
	else
	{
		blockOverFlag[Right] = false;
		gameOverCount[Right] = 0;
	}

}

bool Block::GetDameFlag()
{
	return DamegeFlag;
}

bool Block::GetCheckFlag()
{
	return checkFlag;
}

bool Block::GetAddFlag()
{
	return addFlag;
}

int Block::GetSandDelay()
{
	return sandDelay;
}

int Block::GetComboCount()
{
	return comboCount;
}

int Block::GetColorNumUp()
{
	return checkColorUp;
}

int Block::GetColorNumDown()
{
	return checkColorDown;
}

int Block::GetColorNumLeft()
{
	return checkColorLeft;
}

int Block::GetColorNumRight()
{
	return checkColorRight;
}

void Block::SetSandDelay(int count)
{
	sandDelay = count;
}

int Block::GetGameOverCount(int i)
{
	return gameOverCount[i];
}

bool Block::GetGameOverFlag()
{
	return gameOverFlag;
}