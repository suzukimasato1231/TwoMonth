#include"Enemy.h"
#include<cmath>
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(Sprite *sprite, Object *object, Sound *sound)
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

	assert(sound);
	this->sound = sound;

	Sounddamege = Sound::SoundLoadWave("Resources/Sound/damege.wav");

	enemyPolygon[0] = object->CreateOBJ("redenemy");
	enemyPolygon[1] = object->CreateOBJ("greenenemy");
	enemyPolygon[2] = object->CreateOBJ("bluenemy");
	enemyPolygon[3] = object->CreateOBJ("redblue_enemy");
	enemyPolygon[4] = object->CreateOBJ("greenblue_enemy");
	enemyPolygon[5] = object->CreateOBJ("greenred_enemy");
	enemyPolygon[6] = object->CreateOBJ("rgb1_enemy");
	enemyPolygon[7] = object->CreateOBJ("rgb2_enemy");
	enemyPolygon[8] = object->CreateOBJ("rgb3_enemy");

	//敵の攻撃読み込み
	Polygon = object->CreateOBJ("sphere");
	//エネミー
	for (int i = 0; i < enemy_Num; i++)
	{
		enemyHP[i] = enemyHPKeep[i];
		enemyIsAlive[i] = enemyIsAliveKeep[i];
		enemyIsAttack[i] = enemyIsAttackKeep[i];
		enemyAttackDelay[i] = enemyAttackDelayKeep[i];
		enemyColorTop[i] = enemyColorTopKeep[i];
		enemyColorDown[i] = enemyColorDownKeep[i];
		enemyColorLeft[i] = enemyColorLeftKeep[i];
		enemyColorRight[i] = enemyColorRight[i];
	}
	enemyAttackCount = 0;///攻撃のカウント用

	damege = sprite->SpriteCreate(L"Resources/damege.png");

	damegeHitFlag = false;
	damegeColor = { 1.0f,1.0f,1.0f,0.0f };
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
		enemyColorTop[i] = enemyColorTopKeep[i];
		enemyColorDown[i] = enemyColorDownKeep[i];
		enemyColorLeft[i] = enemyColorLeftKeep[i];
		enemyColorRight[i] = enemyColorRightKeep[i];
	}
	enemyAttackCount = 0;///攻撃のカウント用
	nowPhase = 0;

	eAttackFlag = false;
	shakeTime = 0;

	damegeHitFlag = false;
	damegeColor = { 1.0f,1.0f,1.0f,0.0f };
	memoryHP = 3;
}

void Enemy::Update(int &playerHP, bool DamegeFlag, bool ComboCout, int pTime, bool tutorialFlag)
{
	if (enemyHP[nowPhase] < 0 && enemyIsAlive[nowPhase] == 1 && tutorialFlag == false)
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
			eAttackTime = 125;
		}
		if (eAttackFlag == true && eAttackTime <= 1)
		{
			playerHP--;
			sound->SoundSEPlayWave(Sounddamege);
		}
	}

	//エネミーが体力0以下の時
	if (enemyHP[nowPhase] <= 0)
	{
		enemyDeadFlag = true;
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
	if (enemyDameTime % 10 == 0 && (nowPhase == 0 || enemyHP[nowPhase] >= 0))
	{
		if (nowPhase == 0)
		{
			object->OBJDraw(enemyPolygon[0], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 1)
		{
			object->OBJDraw(enemyPolygon[0], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 2)
		{
			object->OBJDraw(enemyPolygon[1], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 3)
		{
			object->OBJDraw(enemyPolygon[2], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 4)
		{
			object->OBJDraw(enemyPolygon[3], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 5)
		{
			object->OBJDraw(enemyPolygon[4], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 6)
		{
			object->OBJDraw(enemyPolygon[5], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 7)
		{
			object->OBJDraw(enemyPolygon[6], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 8)
		{
			object->OBJDraw(enemyPolygon[7], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 9)
		{
			object->OBJDraw(enemyPolygon[8], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nowPhase == 10)
		{
			object->OBJDraw(enemyPolygon[6], XMFLOAT3(0.0f, -150.0f, -51.0f), XMFLOAT3(75.0f, 75.0f, 10.0f),
				XMFLOAT3(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
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
		eAttackPos.z -= 8.0f;
		if (eAttackTime <= 0)
		{
			damegeHitFlag = true;
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
			damage += damageValueUp[i] + damageValueDown[i] + damageValueLeft[i] + damageValueRight[i];
		}

		double z = std::pow(1.2, combo);
		enemyHP[nowPhase] -= damage * z;
		damage = 0;
		for (int i = 0; i < 100; i++)
		{
			damageValueUp[i] = 0;
			damageValueDown[i] = 0;
			damageValueLeft[i] = 0;
			damageValueRight[i] = 0;
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

bool Enemy::GetEnemyDeadFlag()
{
	return enemyDeadFlag;
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

void Enemy::AttackInit()
{
	enemyAttackCount = 0;///攻撃のカウント用
	eAttackFlag = false;
	shakeTime = 0;
	damegeHitFlag = false;
	damegeColor = { 1.0f,1.0f,1.0f,0.0f };
}

void Enemy::ColorInformationInit()
{
	for (int i = 0; i < 100; i++)
	{
		colorUp[i] = 0;
		colorDown[i] = 0;
		colorLeft[i] = 0;
		colorRight[i] = 0;


		damageValueUp[i] = 0;
		damageValueDown[i] = 0;
		damageValueLeft[i] = 0;
		damageValueRight[i] = 0;

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
		object->OBJDraw(Polygon, eAttackPos, XMFLOAT3{ 1.4f,1.4f,1.4f }, XMFLOAT3{});
	}
}


void Enemy::DrawDamege(int hp)
{
	if (damegeHitFlag == true || hp < memoryHP)
	{
		memoryHP = hp;
		damegeHitFlag = false;
		damegeColor = { 1.0f,1.0f,1.0f,0.8f };
	}
	if (damegeColor.w > 0.0f)
	{
		damegeColor.w -= 0.01f;
	}
	sprite->Draw(damege, XMFLOAT2{}, window_width, window_height, XMFLOAT2(), damegeColor);

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
			if (enemyColorTop[nowPhase] == Red && colorUp[i] == Red) { damageValueUp[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUp[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Red && colorUp[i] == Blue) { damageValueUp[i] = damagaHigh; }
			if (enemyColorTop[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUp[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUp[i] = damageLow; }
			if (enemyColorTop[nowPhase] == Blue && colorUp[i] == Red) { damageValueUp[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUp[i] = damageNormal; }

			if (enemyColorLeft[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeft[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeft[i] = damagaHigh; }
			if (enemyColorLeft[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeft[i] = damageLow; }
			if (enemyColorLeft[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeft[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeft[i] = damageNormal; }

			if (enemyColorRight[nowPhase] == Red && colorRight[i] == Red) { damageValueRight[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRight[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Red && colorRight[i] == Blue) { damageValueRight[i] = damagaHigh; }
			if (enemyColorRight[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRight[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRight[i] = damageLow; }
			if (enemyColorRight[nowPhase] == Blue && colorRight[i] == Red) { damageValueRight[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRight[i] = damageNormal; }

			if (enemyColorDown[nowPhase] == Red && colorDown[i] == Red) { damageValueDown[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDown[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Red && colorDown[i] == Blue) { damageValueDown[i] = damagaHigh; }
			if (enemyColorDown[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDown[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDown[i] = damageLow; }
			if (enemyColorDown[nowPhase] == Blue && colorDown[i] == Red) { damageValueDown[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDown[i] = damageNormal; }
		}
	}
	else if (direction == Down)
	{
		for (int i = 0; i < ComboCount + 1; i++)
		{
			if (enemyColorDown[nowPhase] == Red && colorUp[i] == Red) { damageValueDown[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDown[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Red && colorUp[i] == Blue) { damageValueDown[i] = damagaHigh; }
			if (enemyColorDown[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDown[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDown[i] = damageLow; }
			if (enemyColorDown[nowPhase] == Blue && colorUp[i] == Red) { damageValueDown[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDown[i] = damageNormal; }

			if (enemyColorLeft[nowPhase] == Red && colorRight[i] == Red) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Red && colorRight[i] == Yellow) { damageValueLeft[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Red && colorRight[i] == Blue) { damageValueLeft[i] = damagaHigh; }
			if (enemyColorLeft[nowPhase] == Yellow && colorRight[i] == Red) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueLeft[i] = damageLow; }
			if (enemyColorLeft[nowPhase] == Blue && colorRight[i] == Red) { damageValueLeft[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Blue && colorRight[i] == Blue) { damageValueLeft[i] = damageNormal; }

			if (enemyColorRight[nowPhase] == Red && colorLeft[i] == Red) { damageValueRight[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueRight[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Red && colorLeft[i] == Blue) { damageValueRight[i] = damagaHigh; }
			if (enemyColorRight[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueRight[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueRight[i] = damageLow; }
			if (enemyColorRight[nowPhase] == Blue && colorLeft[i] == Red) { damageValueRight[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueRight[i] = damageNormal; }

			if (enemyColorTop[nowPhase] == Red && colorDown[i] == Red) { damageValueUp[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUp[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Red && colorDown[i] == Blue) { damageValueUp[i] = damagaHigh; }
			if (enemyColorTop[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUp[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUp[i] = damageLow; }
			if (enemyColorTop[nowPhase] == Blue && colorDown[i] == Red) { damageValueUp[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUp[i] = damageNormal; }
		}
	}
	else if (direction == Left)
	{
		for (int i = 0; i < ComboCount + 1; i++)
		{
			if (enemyColorLeft[nowPhase] == Red && colorUp[i] == Red) { damageValueUp[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUp[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Red && colorUp[i] == Blue) { damageValueUp[i] = damagaHigh; }
			if (enemyColorLeft[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUp[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUp[i] = damageLow; }
			if (enemyColorLeft[nowPhase] == Blue && colorUp[i] == Red) { damageValueUp[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUp[i] = damageNormal; }

			if (enemyColorTop[nowPhase] == Red && colorRight[i] == Red) { damageValueRight[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRight[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Red && colorRight[i] == Blue) { damageValueRight[i] = damagaHigh; }
			if (enemyColorTop[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRight[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRight[i] = damageLow; }
			if (enemyColorTop[nowPhase] == Blue && colorRight[i] == Red) { damageValueRight[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRight[i] = damageNormal; }

			if (enemyColorDown[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeft[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeft[i] = damagaHigh; }
			if (enemyColorDown[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeft[i] = damageLow; }
			if (enemyColorDown[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeft[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeft[i] = damageNormal; }

			if (enemyColorRight[nowPhase] == Red && colorDown[i] == Red) { damageValueDown[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDown[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Red && colorDown[i] == Blue) { damageValueDown[i] = damagaHigh; }
			if (enemyColorRight[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDown[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDown[i] = damageLow; }
			if (enemyColorRight[nowPhase] == Blue && colorDown[i] == Red) { damageValueDown[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDown[i] = damageNormal; }
		}
	}
	else if (direction == Right)
	{
		for (int i = 0; i < ComboCount + 1; i++)
		{
			if (enemyColorRight[nowPhase] == Red && colorUp[i] == Red) { damageValueUp[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUp[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Red && colorUp[i] == Blue) { damageValueUp[i] = damagaHigh; }
			if (enemyColorRight[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUp[i] = damageNormal; }
			else if (enemyColorRight[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUp[i] = damageLow; }
			if (enemyColorRight[nowPhase] == Blue && colorUp[i] == Red) { damageValueUp[i] = damageLow; }
			else if (enemyColorRight[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUp[i] = damagaHigh; }
			else if (enemyColorRight[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUp[i] = damageNormal; }

			if (enemyColorTop[nowPhase] == Red && colorLeft[i] == Red) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueLeft[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Red && colorLeft[i] == Blue) { damageValueLeft[i] = damagaHigh; }
			if (enemyColorTop[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueLeft[i] = damageNormal; }
			else if (enemyColorTop[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueLeft[i] = damageLow; }
			if (enemyColorTop[nowPhase] == Blue && colorLeft[i] == Red) { damageValueLeft[i] = damageLow; }
			else if (enemyColorTop[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueLeft[i] = damagaHigh; }
			else if (enemyColorTop[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueLeft[i] = damageNormal; }

			if (enemyColorDown[nowPhase] == Red && colorRight[i] == Red) { damageValueRight[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Red && colorRight[i] == Yellow) { damageValueRight[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Red && colorRight[i] == Blue) { damageValueRight[i] = damagaHigh; }
			if (enemyColorDown[nowPhase] == Yellow && colorRight[i] == Red) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueRight[i] = damageNormal; }
			else if (enemyColorDown[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueRight[i] = damageLow; }
			if (enemyColorDown[nowPhase] == Blue && colorRight[i] == Red) { damageValueRight[i] = damageLow; }
			else if (enemyColorDown[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueRight[i] = damagaHigh; }
			else if (enemyColorDown[nowPhase] == Blue && colorRight[i] == Blue) { damageValueRight[i] = damageNormal; }

			if (enemyColorLeft[nowPhase] == Red && colorDown[i] == Red) { damageValueDown[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDown[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Red && colorDown[i] == Blue) { damageValueDown[i] = damagaHigh; }
			if (enemyColorLeft[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDown[i] = damageNormal; }
			else if (enemyColorLeft[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDown[i] = damageLow; }
			if (enemyColorLeft[nowPhase] == Blue && colorDown[i] == Red) { damageValueDown[i] = damageLow; }
			else if (enemyColorLeft[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDown[i] = damagaHigh; }
			else if (enemyColorLeft[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDown[i] = damageNormal; }
		}
	}
}

int Enemy::GetEnemyColor(int parts)
{
	if (parts == 0)
	{
		return enemyColorDown[nowPhase];
	}
	if (parts == 1)
	{
		return enemyColorRight[nowPhase];
	}
	if (parts == 2)
	{
		return enemyColorLeft[nowPhase];
	}
	if (parts == 3)
	{
		return enemyColorTop[nowPhase];
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
	phaseFlag = false;
	enemyIsAlive[nowPhase] = 0;
	enemyAttackCount = -1;
	nowPhase++;
	enemyDeadFlag = false;
	combo = 0;
}

int Enemy::GetPhaseDelay()
{
	return phaseDelay;
}
