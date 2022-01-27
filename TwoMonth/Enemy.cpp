#include"Enemy.h"
#include<cmath>
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(Sprite *sprite, Object *object)
{
	if (sprite == nullptr)
	{
		assert(sprite);
	}
	this->sprite = sprite;

	if (object == nullptr)
	{
		assert(object);
	}
	this->object = object;

	enemyPolygon[0] = object->CreateRect(300.0f, 300.0f);
	enemyPolygon[1] = object->CreateRect(300.0f, 300.0f);
	enemyPolygon[2] = object->CreateRect(300.0f, 300.0f);

	enemyGraph[0] = object->LoadTexture(L"Resources/redenemy.png");
	enemyGraph[1] = object->LoadTexture(L"Resources/greennemy.png");
	enemyGraph[2] = object->LoadTexture(L"Resources/bluenemy.png");

	//敵の攻撃読み込み
	Polygon = object->CreateOBJ("sphere");
	//エネミー
	for (int i = 0; i < enemy_Num; i++)
	{
		enemyHP[i] = enemyHPKeep[i];
		enemyIsAlive[i] = enemyIsAliveKeep[i];
		enemyIsAttack[i] = enemyIsAttackKeep[i];
		enemyAttackDelay[i] = enemyAttackDelayKeep[i];
		enemyColorTopL[i] = enemyColorTopLKeep[i];
		enemyColorTopR[i] = enemyColorTopRKeep[i];
		enemyColorBottomL[i] = enemyColorBottomLKeep[i];
		enemyColorBottomR[i] = enemyColorBottomRKeep[i];
	}
	enemyAttackCount = 0;///攻撃のカウント用

	/*for (int i = 0; i < 100; i++)
	{
		colorUp[i] = 0;
		colorDown[i] = 0;
		colorLeft[i] = 0;
		colorRight[i] = 0;

		damageValueUpL[i] = 0;
		damageValueUpR[i] = 0;
		damageValueDownL[i] = 0;
		damageValueDownR[i] = 0;
		damageValueLeftL[i] = 0;
		damageValueLeftR[i] = 0;
		damageValueRightL[i] = 0;
		damageValueRightR[i] = 0;

		damageValue[i] = 0;
	}*/
}

void Enemy::MainInit()
{
	//エネミー
	for (int i = 0; i < enemy_Num; i++)
	{
		enemyHP[i] = enemyHPKeep[i];
		enemyIsAlive[i] = enemyIsAliveKeep[i];
		enemyIsAttack[i] = enemyIsAttackKeep[i];
		enemyAttackDelay[i] = enemyAttackDelayKeep[i];
		enemyColorTopL[i] = enemyColorTopLKeep[i];
		enemyColorTopR[i] = enemyColorTopRKeep[i];
		enemyColorBottomL[i] = enemyColorBottomLKeep[i];
		enemyColorBottomR[i] = enemyColorBottomRKeep[i];
	}
	enemyAttackCount = 0;///攻撃のカウント用

	/*for (int i = 0; i < 100; i++)
	{
		colorUp[i] = 0;
		colorDown[i] = 0;
		colorLeft[i] = 0;
		colorRight[i] = 0;

		damageValueUpL[i] = 0;
		damageValueUpR[i] = 0;
		damageValueDownL[i] = 0;
		damageValueDownR[i] = 0;
		damageValueLeftL[i] = 0;
		damageValueLeftR[i] = 0;
		damageValueRightL[i] = 0;
		damageValueRightR[i] = 0;

		damageValue[i] = 0;
	}*/
	eAttackFlag = false;
	shakeTime = 0;
}

void Enemy::Update(int &playerHP, bool DamegeFlag, bool ComboCout, int pTime)
{
	if (enemyHP[nowPhase] < 0 && enemyIsAlive[nowPhase] == 1)
	{
		phaseFlag = true;
	}
	if (enemyIsAlive[nowPhase] == true)
	{
		if (DamegeFlag == true && eAttackFlag == false && pTime < 11)
		{
			enemyAttackCount++;
		}
		if (enemyAttackCount == enemyAttackDelay[nowPhase])
		{
			enemyIsAttack[nowPhase] = true;
		}
		if (enemyIsAttack[nowPhase] == true)
		{
			enemyAttackCount = 0;
			enemyIsAttack[nowPhase] = false;
			eAttackFlag = true;
			eAttackPos = { 0.0f,0.0f,0.0f };
			eAttackTime = 100;
		}
		if (eAttackFlag == true && eAttackTime <= 1)
		{
			playerHP--;
		}
	}

	
		
	
	//ダメージ食らったときの点滅
	if (enemyDameDirecting == true)
	{
		enemyDameTime++;
		if (enemyDameTime >= 100)
		{
			enemyDameDirecting = false;
		}
	}
	else
	{
		enemyDameTime = 0;
	}
}

void Enemy::Draw()
{
	if (enemyDameTime % 10 == 0)
	{
		if (nowPhase == 0 || nowPhase == 3 || nowPhase == 6 || nowPhase == 9 || nowPhase == 12 || nowPhase == 15 || nowPhase == 18)
		{
			object->Draw(enemyPolygon[0], XMFLOAT3(0.0f, 0.0f, -51.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), enemyGraph[0]);
		}
		if (nowPhase == 1 || nowPhase == 4 || nowPhase == 7 || nowPhase == 10 || nowPhase == 13 || nowPhase == 16 || nowPhase == 19)
		{
			object->Draw(enemyPolygon[1], XMFLOAT3(0.0f, 0.0f, -51.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), enemyGraph[1]);
		}
		if (nowPhase == 2 || nowPhase == 5 || nowPhase == 8 || nowPhase == 11 || nowPhase == 14 || nowPhase == 17)
		{
			object->Draw(enemyPolygon[2], XMFLOAT3(0.0f, 0.0f, -51.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), enemyGraph[2]);
		}
	}
}

void Enemy::PhaseUpdate(bool CheckFlag, bool DamegeFlag, int ComboCount,
	int colorNumUP, int colorNumDown, int colorNumLeft, int colorNumRight, int direction)
{
	DamageCheck(ComboCount, direction);
	//HpBar = 1180 * ((enemyHP[nowPhase] /enemyHPKeep[nowPhase]));
	if (phaseFlag == true)
	{
		phaseDelay++;
		//フェーズが変わったら点滅しない
		enemyDameDirecting = false;
		enemyDameTime = 0;
	}
	else if (phaseFlag == false)
	{
		phaseDelay = 0;
	}

	if (CheckFlag == true)
	{
		colorUp[ComboCount] = colorNumUP;
		colorDown[ComboCount] = colorNumDown;
		colorLeft[ComboCount] = colorNumLeft;
		colorRight[ComboCount] = colorNumRight;
	}

	//敵の攻撃座標更新
	if (eAttackFlag == true)
	{
		eAttackTime--;
		eAttackPos.z -= 10.0f;
		if (eAttackTime <= 0)
		{
			eAttackFlag = false;
			ShakeStart(20.0f, 20);
		}
	}
	ShakeUpdate();
	//betaDamageCheck(ComboCount);
	if (DamegeFlag == false)
	{
		combo = ComboCount;

		if (ComboCount > 0)
		{
			int i = 0;
		}
	}

	DamegeCal(DamegeFlag);
}

void Enemy::DamegeCal(bool DamegeFlag)
{
	if (DamegeFlag == true)
	{
		for (int i = 0; i < 100; i++)
		{
			damage += damageValueUpL[i] + damageValueUpR[i] + damageValueDownL[i] + damageValueDownR[i] + damageValueLeftL[i] + damageValueLeftR[i] + damageValueRightL[i] + damageValueRightR[i];
		}
		double z = std::pow(1.2, combo);
		enemyHP[nowPhase] -= damage * z;
		damage = 0;
		for (int i = 0; i < 100; i++)
		{
			damageValueUpL[i] = 0;
			damageValueUpR[i] = 0;
			damageValueDownL[i] = 0;
			damageValueDownR[i] = 0;
			damageValueLeftL[i] = 0;
			damageValueLeftR[i] = 0;
			damageValueRightL[i] = 0;
			damageValueRightR[i] = 0;
		}
		ColorInformationInit();
		enemyDameDirecting = true;
	}

}
int Enemy::GetAttackCount()
{
	return enemyAttackCount;
}
int Enemy::GetAttackDelay()
{
	return enemyAttackDelay[nowPhase];
}
float Enemy::GetEnemyHP()
{
	return enemyHP[nowPhase];
}

float Enemy::GetConstEnemyHP()
{
	return enemyHPKeep[nowPhase];
}

int Enemy::GetCombo()
{
	return combo;
}

double Enemy::GetHpBar()
{
	return HpBar;
}

void Enemy::ShakeUpdate()
{
	//シェイク初期化
	shakePos = { 0.0f,0.0f };
	//シェイクが続く時間
	if (shakeTime > 0)
	{
		shakePos.x = (rand() % shakeString - shakeString / 2) * shkeStringTime;
		shakePos.y = (rand() % shakeString - shakeString / 2) * shkeStringTime;
		shakeTime -= 1;
		shkeStringTime -= 0.1f;
	}
}

XMFLOAT2 Enemy::GetShakePos()
{
	return shakePos;
}

bool Enemy::GeteAttackFlag()
{
	return eAttackFlag;
}

void Enemy::ColorInformationInit()
{
	for (int i = 0; i < 100; i++)
	{
		colorUp[i] = 0;
		colorDown[i] = 0;
		colorLeft[i] = 0;
		colorRight[i] = 0;


		damageValueUpL[i] = 0;
		damageValueUpR[i] = 0;
		damageValueDownL[i] = 0;
		damageValueDownR[i] = 0;
		damageValueLeftL[i] = 0;
		damageValueLeftR[i] = 0;
		damageValueRightL[i] = 0;
		damageValueRightR[i] = 0;
		damageValue[i] = 0;
	}
}



void Enemy::ShakeStart(float shakeTime, int shakeString)
{
	//シェイクする時間
	this->shakeTime = shakeTime;
	//シェイクの強さ
	this->shakeString = shakeString;
	//減衰
	shkeStringTime = shakeTime / 10;
	shakeFlag = false;
}


bool Enemy::GetphaseFlag()
{
	return phaseFlag;
}



void Enemy::AttackDraw()
{
	//エネミー攻撃描画場所
	if (eAttackFlag == true)
	{
		object->OBJDraw(Polygon, eAttackPos, XMFLOAT3{ 1.2f,1.2f,1.2f }, XMFLOAT3{});
	}
}

void Enemy::betaDamageCheck(int ComboCount)
{
	if (enemyColor[nowPhase] == Red)
	{
		for (int i = 0; i < ComboCount; i++)
		{
			if (colorUp[i + 1] == Red) { damageUpValue[i] = damageNormal; }
			else if (colorUp[i + 1] == Yellow) { damageUpValue[i] = damageLow; }
			else if (colorUp[i + 1] == Blue) { damageUpValue[i] = damagaHigh; }
			if (colorDown[i + 1] == Red) { damageDownValue[i] = damageNormal; }
			else if (colorDown[i + 1] == Yellow) { damageDownValue[i] = damageLow; }
			else if (colorDown[i + 1] == Blue) { damageDownValue[i] = damagaHigh; }
			if (colorLeft[i + 1] == Red) { damageLeftValue[i] = damageNormal; }
			else if (colorLeft[i + 1] == Yellow) { damageLeftValue[i] = damageLow; }
			else if (colorLeft[i + 1] == Blue) { damageLeftValue[i] = damagaHigh; }
			if (colorRight[i + 1] == Red) { damageRightValue[i] = damageNormal; }
			else if (colorRight[i + 1] == Yellow) { damageRightValue[i] = damageLow; }
			else if (colorRight[i + 1] == Blue) { damageRightValue[i] = damagaHigh; }
		}
	}
	else if (enemyColor[nowPhase] == Yellow)
	{
		for (int i = 0; i < ComboCount; i++)
		{
			if (colorUp[i] == Red) { damageUpValue[i] = damagaHigh; }
			else if (colorUp[i] == Yellow) { damageUpValue[i] = damageNormal; }
			else if (colorUp[i] == Blue) { damageUpValue[i] = damageLow; }
			if (colorDown[i] == Red) { damageDownValue[i] = damagaHigh; }
			else if (colorDown[i] == Yellow) { damageDownValue[i] = damageNormal; }
			else if (colorDown[i] == Blue) { damageDownValue[i] = damageLow; }
			if (colorLeft[i] == Red) { damageLeftValue[i] = damagaHigh; }
			else if (colorLeft[i] == Yellow) { damageLeftValue[i] = damageNormal; }
			else if (colorLeft[i] == Blue) { damageLeftValue[i] = damageLow; }
			if (colorRight[i] == Red) { damageRightValue[i] = damagaHigh; }
			else if (colorRight[i] == Yellow) { damageRightValue[i] = damageNormal; }
			else if (colorRight[i] == Blue) { damageRightValue[i] = damageLow; }
		}
	}
	else if (enemyColor[nowPhase] == Blue)
	{
		for (int i = 0; i < ComboCount; i++)
		{
			if (colorUp[i] == Red) { damageUpValue[i] = damageLow; }
			else if (colorUp[i] == Yellow) { damageUpValue[i] = damagaHigh; }
			else if (colorUp[i] == Blue) { damageUpValue[i] = damageNormal; }
			if (colorDown[i] == Red) { damageDownValue[i] = damageLow; }
			else if (colorDown[i] == Yellow) { damageDownValue[i] = damagaHigh; }
			else if (colorDown[i] == Blue) { damageDownValue[i] = damageNormal; }
			if (colorLeft[i] == Red) { damageLeftValue[i] = damageLow; }
			else if (colorLeft[i] == Yellow) { damageLeftValue[i] = damagaHigh; }
			else if (colorLeft[i] == Blue) { damageLeftValue[i] = damageNormal; }
			if (colorRight[i] == Red) { damageRightValue[i] = damageLow; }
			else if (colorRight[i] == Yellow) { damageRightValue[i] = damagaHigh; }
			else if (colorRight[i] == Blue) { damageRightValue[i] = damageNormal; }
		}
	}
}

void Enemy::DamageCheck(int ComboCount, int direction)
{
	if (direction == UP)
	{
		for (int i = 1; i < ComboCount + 1; i++)
		{
			if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Red)
			{
				damageValueUpL[i] = damageNormal;
			}
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damageLow; }
			if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpL[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpL[i] = damageNormal; }

			if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpR[i] = damageLow; }
			if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpR[i] = damageNormal; }


			if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeftR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeftR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeftR[i] = damageLow; }
			if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeftR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeftR[i] = damageNormal; }

			if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeftL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeftL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeftL[i] = damageLow; }
			if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeftL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeftL[i] = damageNormal; }


			if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Red) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Blue) { damageValueRightL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRightL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRightL[i] = damageLow; }
			if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Red) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRightL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRightL[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Red) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Blue) { damageValueRightR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRightR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRightR[i] = damageLow; }
			if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Red) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRightR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRightR[i] = damageNormal; }


			if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = damageLow; }
			if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Red) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownL[i] = damageLow; }
			if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownL[i] = damageNormal; }
		}
	}
	else if (direction == Down)
	{
		for (int i = 0; i < ComboCount + 1; i++)
		{
			if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Red)
			{
				damageValueDownL[i] = damageNormal;
			}
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownL[i] = damageLow; }
			if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownL[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownR[i] = damageLow; }
			if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }

			if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Red) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Blue) { damageValueLeftL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueLeftL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueLeftL[i] = damageNormal; }
			if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Red) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueLeftL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueLeftL[i] = damageNormal; }

			if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Red) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Blue) { damageValueLeftR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueLeftR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueLeftR[i] = damageNormal; }
			if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Red) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueLeftR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueLeftR[i] = damageNormal; }


			if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Red) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueRightR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueRightR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueRightR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueRightR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueRightR[i] = damageNormal; }

			if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Red) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueRightL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueRightL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueRightL[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueRightL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueRightL[i] = damageNormal; }


			if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpR[i] = damageNormal; }
			if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Red) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUpR[i] = damageNormal; }

			if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Red) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUpL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUpL[i] = damageNormal; }
		}
	}
	else if (direction == Left)
	{
		for (int i = 0; i < ComboCount + 1; i++)
		{
			if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpR[i] = damageNormal; }

			if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpL[i] = damageNormal; }

			if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Red) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Blue) { damageValueRightL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRightL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Red) { damageValueRightL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRightL[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRightL[i] = damageNormal; }

			if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Red) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRightR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Blue) { damageValueRightR[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRightR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRightR[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Red) { damageValueRightR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRightR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRightR[i] = damageNormal; }

			if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeftR[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeftR[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeftR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeftR[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeftL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeftL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeftL[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeftL[i] = damageNormal; }

			if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Red) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownL[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
		}
	}
	else if (direction == Right)
	{
		for (int i = 0; i < ComboCount + 1; i++)
		{
			if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpL[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpL[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpR[i] = damageNormal; }

			if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeftR[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeftR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeftR[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeftR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeftR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeftR[i] = damageNormal; }

			if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeftL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeftL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeftL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeftL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeftL[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeftL[i] = damageNormal; }

			if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Red) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRightL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Blue) { damageValueRightL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRightL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRightL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRightL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Red) { damageValueRightL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRightL[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRightL[i] = damageNormal; }

			if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Red) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Blue) { damageValueRightR[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRightR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRightR[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Red) { damageValueRightR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRightR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRightR[i] = damageNormal; }

			if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Red) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownL[i] = damageNormal; }

			if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
		}
	}
}

int Enemy::GetDamegeValue(int i, int angle)
{
	if (angle == 0)
	{
		return colorUp[i];
	}
	if (angle == 1)
	{
		return colorDown[i];
	}
	if (angle == 2)
	{
		return colorLeft[i];
	}
	if (angle == 3)
	{
		return colorRight[i];
	}
}

int Enemy::GetEnemyLastHP()
{
	return enemyHP[enemy_Num - 1];
}

void Enemy::FlagChenge()
{
	phaseFlag = 0;
	enemyIsAlive[nowPhase] = 0;
	enemyAttackCount = -1;
	nowPhase++;
}

int Enemy::GetPhaseDelay()
{
	return phaseDelay;
}
