#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
GameSceneManager::GameSceneManager()
{
}
GameSceneManager::~GameSceneManager()
{
	safe_delete(object);
	safe_delete(sprite);
	safe_delete(particleMan);
	safe_delete(light);
	//XAudio2解放
	sound->xAudio2.Reset();
	//音データ解放
	Sound::SoundUnload(&sound1);
	Sound::SoundUnload(&sound2);
	safe_delete(sound);
}
void GameSceneManager::Initialize(Input *input, _DirectX *directX)
{
	assert(input);
	this->input = input;
	assert(directX);
	this->directX = directX;
	sound = Sound::Create();
	view = View::Create();
	sprite = Sprite::Create();
	object = Object::Create();
	ParticleManager::StaticInitialize(directX->GetDevice(), directX->GetCmandList(), this->view, window_width, window_height);
	particleMan = ParticleManager::Create();
	light = Light::Create();
	//初期化
	debugText.Initialize();
	object->Init(directX->GetDevice(), directX->GetCmandList(), view, light);
}

void GameSceneManager::Init()
{
	/*sound1 = Sound::SoundLoadWave("Resources/i.wav");
	sound2 = Sound::SoundLoadWave("Resources/BGM.wav");
	sound->SoundSEPlayWave(sound1);
	sound->SoundBGMPlayLoopWave(sound2, sound->BGM);*/

	//カメラ
	view->SetViewCamera(XMFLOAT3{ 0,0,-200 }, XMFLOAT3{ 0, 0, 0 }, XMFLOAT3{ 0, 1, 0 });

	//ライト色を設定
	light->SetLightColor({ 1,1,1 });

	//スプライト画像読み込み
	//spriteGraph = sprite->SpriteCreate(L"Resources/text2.jpg");
	BGGraph = sprite->SpriteCreate(L"Resources/background.png");
	enemyGraph = sprite->SpriteCreate(L"Resources/enemy.png");
	phaseGraph = sprite->SpriteCreate(L"Resources/phaseclear.png");

	//オブジェクト画像読み込み
	//graph1 = object->LoadTexture(L"Resources/texture2.jpg");
	//graph3 = object->LoadTexture(L"Resources/white.png");

	//オブジェクト生成
	//Polygon = object->CreateOBJ("Boss");
	//BossPolygon = object->CreateOBJ("sphere", true);

	//台クラス初期化
	table.Init(input, sprite);
	//ブロッククラス
	block.Init(input, sprite);

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

void GameSceneManager::Update()
{
	if (input->KeybordPush(DIK_R))
	{
		table.MainInit();
		block.MainInit();
		//プレイヤーステータス
		playerHP = 3;///体力
		playerIsAlive = 1;///存在するか
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
	}
	if (phaseFlag == 0)
	{
		table.Update();

		block.Update(&table.table, table.GetStatus());

		block.ColBlock(&table.table, table.GetPos(), table.GetStatus());

		table.ShakeGet(block.GetShakeFlag());

		if (block.GetDameFlag() == true)
		{
			DamageCheck();
			enemyHP[nowPhase] -= damage;
		}
		if (enemyHP[nowPhase] == 0 && enemyIsAlive[nowPhase] == 1)
		{
			phaseFlag = 1;
		}
		if (enemyIsAlive[nowPhase] == true)
		{
			if (block.GetDameFlag() == true)
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
			}
		}
		/*if (enemyHP[nowPhase] == 0 )
		{
			nowPhase++;
			enemyIsAlive[nowPhase] = 0;
		}*/
		if (block.GetComboCount() == 0)
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
	}
	if (phaseFlag == 1)
	{
		phaseDelay++;
	}
	else if (phaseFlag == 0)
	{
		phaseDelay = 0;
	}

	if (phaseDelay > 120)
	{
		phaseFlag = 0;
		block.DeleteBlock();
		enemyIsAlive[nowPhase] = 0;
		enemyAttackCount = -1;
		nowPhase++;
	}

	if (block.GetCheckFlag() == true)
	{
		colorUp[block.GetComboCount() - 1] = block.GetColorNumUp();
		colorDown[block.GetComboCount() - 1] = block.GetColorNumDown();
		colorLeft[block.GetComboCount() - 1] = block.GetColorNumLeft();
		colorRight[block.GetComboCount() - 1] = block.GetColorNumRight();
	}
	ColorDamageCheck();
	//パーティクル更新
	//particleMan->ParticleAdd(pPos1);
	particleMan->Update();
	//ライト更新
	light->Update();
}

void GameSceneManager::Draw(_DirectX directX)
{
	//オブジェクト描画前処理
	object->PreDraw();
	sprite->PreDraw();

	//背景描画
	sprite->Draw(BGGraph, XMFLOAT2{ 0.0f,0.0f }, window_width, window_height);


	//オブジェクト
	//object->OBJDraw(Polygon, pPos1, XMFLOAT3{ 1.0f,1.0f,1.0f }, angle, XMFLOAT4{ 1.0f,1.0f,1.0f ,1.0f });
	//object->OBJDraw(Polygon, pPos2, XMFLOAT3{ 1.0f,1.0f,1.0f }, angle, XMFLOAT4{ 1.0f,1.0f,1.0f ,1.0f });


	table.Draw();

	block.Draw();

	//パーティクル描画
	particleMan->Draw();


	//前景描画
	//sprite->Draw(spriteGraph, XMFLOAT2(0, 0), 100, 100);
	sprite->Draw(enemyGraph, XMFLOAT2(window_width / 2 - 46, window_height / 2 - 46), 100, 100);

	if (phaseFlag == 1)
	{
		sprite->Draw(phaseGraph, XMFLOAT2(0, 0), 1920, 1080);
	}

	switch (table.GetStatus())
	{
	case UP:
		debugText.Print(1, 120, 2, "direction:UP");
		break;
	case Down:
		debugText.Print(1, 120, 2, "direction:Down");
		break;
	case Left:
		debugText.Print(1, 120, 2, "direction:Left");
		break;
	case Right:
		debugText.Print(1, 120, 2, "direction:Right");
		break;
	}

	debugText.Print(1, 30, 2, "AD:rotation");
	debugText.Print(1, 60, 2, "yazirusi:position");

	debugText.Print(10, 140, 2, "   playerHP :%d", playerHP);
	debugText.Print(10, 180, 2, "    enemyHP :%d", enemyHP[nowPhase]);
	debugText.Print(10, 220, 2, "      phese :%d", nowPhase + 1);
	debugText.Print(10, 260, 2, "enemyAttack :%d", enemyAttackCount);
	debugText.Print(10, 300, 2, "         d  :%f", damage);
	debugText.Print(10, 340, 2, "            :%d", block.GetSandDelay());
	debugText.Print(10, 380, 2, "         d  :%f");
	debugText.Print(10, 420, 2, "         d  :%f");
	//debugText.Print(10, 380, 2, "      combo :%d", block.GetComboCount());
	//debugText.Print(10, 420, 2, "    colorUp :%d", block.GetColorNumUp());
	//debugText.Print(10, 460, 2, "  colorDown :%d", block.GetColorNumDown());
	//debugText.Print(10, 500, 2, "  colorLeft :%d", block.GetColorNumLeft());
	//debugText.Print(10, 540, 2, " colorRight :%d", block.GetColorNumRight());
	//debugText.Print(10, 120, 2, "            :%d", block.GetSandDelay());
	//debugText.Print(10, 160, 2, "      combo :%d", block.GetComboCount());
	//debugText.Print(10, 200 + 0 * 40, 2, " color :%d %d %d %d", colorUp[0], colorDown[0], colorLeft[0], colorRight[0]);
	//debugText.Print(10, 200 + 1 * 40, 2, " color :%d %d %d %d", colorUp[1], colorDown[1], colorLeft[1], colorRight[1]);
	//debugText.Print(10, 200 + 2 * 40, 2, " color :%d %d %d %d", colorUp[2], colorDown[2], colorLeft[2], colorRight[2]);
	//debugText.Print(10, 200 + 3 * 40, 2, " color :%d %d %d %d", colorUp[3], colorDown[3], colorLeft[3], colorRight[3]);
	//debugText.Print(10, 200 + 4 * 40, 2, " color :%d %d %d %d", colorUp[4], colorDown[4], colorLeft[4], colorRight[4]);
	//debugText.Print(10, 200 + 5 * 40, 2, " color :%d %d %d %d", colorUp[5], colorDown[5], colorLeft[5], colorRight[5]);
	//debugText.Print(10, 200 + 6 * 40, 2, " color :%d %d %d %d", colorUp[6], colorDown[6], colorLeft[6], colorRight[6]);
	//debugText.Print(10, 200 + 7 * 40, 2, " color :%d %d %d %d", colorUp[7], colorDown[7], colorLeft[7], colorRight[7]);
	//debugText.Print(10, 200 + 8 * 40, 2, " color :%d %d %d %d", colorUp[8], colorDown[8], colorLeft[8], colorRight[8]);
	//debugText.Print(10, 200 + 9 * 40, 2, " color :%d %d %d %d", colorUp[9], colorDown[9], colorLeft[9], colorRight[9]);
	//debugText.Print(10, 200 + 10 * 40, 2, " color :%d %d %d %d", colorUp[10], colorDown[10], colorLeft[10], colorRight[10]);

	debugText.Print(10, 200 + 12 * 40, 2, " UPgameOverTime :%d", block.GetGameOverCount(0));
	debugText.Print(10, 200 + 13 * 40, 2, "DowngameOverTime:%d", block.GetGameOverCount(1));
	debugText.Print(10, 200 + 14 * 40, 2, " LeftgameOverTime:%d ", block.GetGameOverCount(2));
	debugText.Print(10, 200 + 15 * 40, 2, " RightgameOverTime:%d ", block.GetGameOverCount(3));

	if (block.GetGameOverFlag() == TRUE)
	{
		debugText.Print(10, 200 + 16 * 40, 2, " GAMEOVER");
	}
	//デバックテキスト描画
	debugText.
		DrawAll();
}

void GameSceneManager::ColorDamageCheck()
{
	if (table.GetStatus() == UP)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///上2つ
			if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = 100; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = 50; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = 200; }
			if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = 200; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = 100; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = 50; }
			if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpL[i] = 50; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpL[i] = 200; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpL[i] = 100; }
			if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpR[i] = 100; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpR[i] = 50; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpR[i] = 200; }
			if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpR[i] = 200; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpR[i] = 100; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpR[i] = 50; }
			if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpR[i] = 50; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpR[i] = 200; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpR[i] = 100; }

			///下2つ
			if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = 0; }

			///左2つ
			if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownL[i] = 0; }

			///右2つ
			if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = 0; }
		}
	}
	else if (table.GetStatus() == Down)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///下2つ
			if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = 0; }

			///上2つ
			if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUpR[i] = 0; }

			///右2つ
			if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = 0; }

			///左2つ
			if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownL[i] = 0; }
		}
	}
	else if (table.GetStatus() == Left)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///右2つ
			if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = 0; }

			///左2つ
			if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUpL[i] = 0; }

			///上2つ
			if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueUpR[i] = 0; }

			///下2つ
			if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = 0; }
		}
	}
	else if (table.GetStatus() == Right)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///左2つ
			if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownL[i] = 0; }

			///右2つ
			if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = 0; }


			///下2つ
			if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownL[i] = 0; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownL[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownR[i] = 0; }
			if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = 0; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = 0; }

			///上2つ
			if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Red) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueUpL[i] = 0; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueUpL[i] = 0; }
			if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpR[i] = 0; }
			if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Red) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueUpR[i] = 0; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueUpR[i] = 0; }
		}
	}
}

void GameSceneManager::DamageCheck()
{
	for (int i = 0; i < block.GetComboCount(); i++)
	{
		damageValue[i] = (damageValueUpL[i] + damageValueDownL[i] + damageValueLeftL[i] + damageValueRightL[i] + damageValueUpR[i] + damageValueDownR[i] + damageValueLeftR[i] + damageValueRightR[i]) * (1.2 * (i + 1));
	}

	for (int i = 0; i < block.GetComboCount(); i++)
	{
		damage += damageValue[i];
	}
}
