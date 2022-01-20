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

	enemyGraph[0] = sprite->SpriteCreate(L"Resources/redenemy.png");
	enemyGraph[1] = sprite->SpriteCreate(L"Resources/greennemy.png");
	enemyGraph[2] = sprite->SpriteCreate(L"Resources/bluenemy.png");
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

void Enemy::Update(int &playerHP, bool DamegeFlag, bool ComboCout)
{
	if (enemyHP[nowPhase] < 0 && enemyIsAlive[nowPhase] == 1)
	{
		phaseFlag = 1;
	}
	if (enemyIsAlive[nowPhase] == true)
	{
		if (DamegeFlag == true)
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
			playerHP--;
			enemyIsAttack[nowPhase] = false;
			eAttackFlag = true;
			eAttackPos = { 0.0f,0.0f,0.0f };
			eAttackTime = 50;
		}
	}

	if (ComboCout == 0)
	{
		ColorInformationInit();
	}
}

void Enemy::Draw()
{
	if (nowPhase == 0 || nowPhase == 3 || nowPhase == 6 || nowPhase == 9 || nowPhase == 12 || nowPhase == 15 || nowPhase == 18)
	{
		sprite->Draw(enemyGraph[0], XMFLOAT2(window_width / 2 - 133, 470), 250, 250);
	}
	if (nowPhase == 1 || nowPhase == 4 || nowPhase == 7 || nowPhase == 10 || nowPhase == 13 || nowPhase == 16 || nowPhase == 19)
	{
		sprite->Draw(enemyGraph[1], XMFLOAT2(window_width / 2 - 133, 470), 250, 250);
	}
	if (nowPhase == 2 || nowPhase == 5 || nowPhase == 8 || nowPhase == 11 || nowPhase == 14 || nowPhase == 17)
	{
		sprite->Draw(enemyGraph[2], XMFLOAT2(window_width / 2 - 133, 470), 250, 250);
	}
}

void Enemy::PhaseUpdate(bool CheckFlag, bool DamegeFlag, int ComboCount,
	int colorNumUP, int colorNumDown, int colorNumLeft, int colorNumRight)
{
	if (phaseFlag == 1)
	{
		phaseDelay++;
	}
	else if (phaseFlag == 0)
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
		eAttackPos.z -= 5.0f;
		if (eAttackTime <= 0)
		{
			eAttackFlag = false;
			ShakeStart(20.0f, 20);
		}
	}
	ShakeUpdate();
	betaDamageCheck(ComboCount);
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
			damage += damageUpValue[i] + damageDownValue[i] + damageLeftValue[i] + damageRightValue[i];
		}
		double z = std::pow(1.2, combo);
		enemyHP[nowPhase] -= damage * z;
		damage = 0;
		for (int i = 0; i < 100; i++)
		{
			damageUpValue[i] = 0;
			damageDownValue[i] = 0;
			damageLeftValue[i] = 0;
			damageRightValue[i] = 0;
		}
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
int Enemy::GetEnemyHP()
{
	return enemyHP[nowPhase];
}
int Enemy::GetCombo()
{
	return combo;
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
		object->OBJDraw(Polygon, eAttackPos, XMFLOAT3{ 1.0f,1.0f,1.0f }, XMFLOAT3{});
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
