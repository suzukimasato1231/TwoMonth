#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include<cmath>
GameSceneManager::GameSceneManager()
{
}
GameSceneManager::~GameSceneManager()
{
	safe_delete(object);
	safe_delete(sprite);
	safe_delete(particleMan);
	safe_delete(light);
	//XAudio2���
	sound->xAudio2.Reset();
	//���f�[�^���
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
	//������
	debugText.Initialize();
	object->Init(directX->GetDevice(), directX->GetCmandList(), view, light);
}

void GameSceneManager::Init()
{
	/*sound1 = Sound::SoundLoadWave("Resources/i.wav");
	sound2 = Sound::SoundLoadWave("Resources/BGM.wav");
	sound->SoundSEPlayWave(sound1);
	sound->SoundBGMPlayLoopWave(sound2, sound->BGM);*/

	//�J����
	view->SetViewCamera(XMFLOAT3{ 0,0,-200 }, XMFLOAT3{ 0, 0, 0 }, XMFLOAT3{ 0, 1, 0 });

	//���C�g�F��ݒ�
	light->SetLightColor({ 1,1,1 });

	//�X�v���C�g�摜�ǂݍ���
	//spriteGraph = sprite->SpriteCreate(L"Resources/text2.jpg");
	BGGraph = sprite->SpriteCreate(L"Resources/background.png");
	BG2Graph = sprite->SpriteCreate(L"Resources/background2.png");
	enemyGraph[0]= sprite->SpriteCreate(L"Resources/redenemy.png");
	enemyGraph[1] = sprite->SpriteCreate(L"Resources/greennemy.png");
	enemyGraph[2] = sprite->SpriteCreate(L"Resources/bluenemy.png");
	phaseGraph = sprite->SpriteCreate(L"Resources/phaseclear.png");
	UIGraph = sprite->SpriteCreate(L"Resources/UI1.png");
	GameOverGraph = sprite->SpriteCreate(L"Resources/gameover.png");
	titleGraph = sprite->SpriteCreate(L"Resources/1.png");
	numGraph[0] = sprite->SpriteCreate(L"Resources/number/0.png");
	numGraph[1] = sprite->SpriteCreate(L"Resources/number/1.png");
	numGraph[2] = sprite->SpriteCreate(L"Resources/number/2.png");
	numGraph[3] = sprite->SpriteCreate(L"Resources/number/3.png");
	numGraph[4] = sprite->SpriteCreate(L"Resources/number/4.png");
	numGraph[5] = sprite->SpriteCreate(L"Resources/number/5.png");
	numGraph[6] = sprite->SpriteCreate(L"Resources/number/6.png");
	numGraph[7] = sprite->SpriteCreate(L"Resources/number/7.png");
	numGraph[8] = sprite->SpriteCreate(L"Resources/number/8.png");
	numGraph[9] = sprite->SpriteCreate(L"Resources/number/9.png");
	//�I�u�W�F�N�g�摜�ǂݍ���
	//graph1 = object->LoadTexture(L"Resources/texture2.jpg");
	//graph3 = object->LoadTexture(L"Resources/white.png");

	//�I�u�W�F�N�g����
	Polygon = object->CreateOBJ("sphere");
	//BossPolygon = object->CreateOBJ("sphere", true);

	//��N���X������
	table.Init(input, sprite);
	//�u���b�N�N���X
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
	//�V�[���Ǘ��̓y��
	switch (scene)
	{
	case TitleInit:

		table.MainInit();
		block.MainInit();
		//�v���C���[�X�e�[�^�X
		playerHP = 3;///�̗�
		playerIsAlive = 1;///���݂��邩
		//�G�l�~�[
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
		enemyAttackCount = 0;///�U���̃J�E���g�p
		scene = Title;
	case Title:
		if (input->KeybordTrigger(DIK_SPACE))
		{
			scene = MainInit;
		}
		break;
	case MainInit:
		table.MainInit();
		block.MainInit();
		scene = Main;
	case Main:
		if (input->KeybordPush(DIK_R))
		{
			table.MainInit();
			block.MainInit();
			//�v���C���[�X�e�[�^�X
			playerHP = 3;///�̗�
			playerIsAlive = 1;///���݂��邩
			//�G�l�~�[
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
			enemyAttackCount = 0;///�U���̃J�E���g�p
		}
		if (phaseFlag == 0)
		{
			table.Update();

			block.Update(&table.table, table.GetStatus());

			block.ColBlock(&table.table, table.GetPos(), table.GetStatus());

			table.ShakeGet(block.GetShakeFlag());

			if (enemyHP[nowPhase] < 0 && enemyIsAlive[nowPhase] == 1)
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
					eAttackFlag = true;
					eAttackPos = { 0.0f,0.0f,0.0f };
					eAttackTime = 50;
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
			phaseNum++;
		}

		if (block.GetCheckFlag() == true)
		{
			colorUp[block.GetComboCount()] = block.GetColorNumUp();
			colorDown[block.GetComboCount()] = block.GetColorNumDown();
			colorLeft[block.GetComboCount()] = block.GetColorNumLeft();
			colorRight[block.GetComboCount()] = block.GetColorNumRight();
		}
		//ColorDamageCheck();
		//DamageCheck();
		/*if (input->KeybordTrigger(DIK_L))
		{
			eAttackFlag = true;
			eAttackPos = { 0.0f,0.0f,0.0f };
			eAttackTime = 50;
		}*/
		//�G�̍U�����W�X�V
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
		betaDamageCheck();
		if (block.GetDameFlag() == false)
		{
			combo = block.GetComboCount();
		}
		if (block.GetDameFlag() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				damage += damageUpValue[i] + damageDownValue[i] + damageLeftValue[i] + damageRightValue[i];
			}
			double z = std::pow(1.2,combo);
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
		if (phaseNum == 10)
		{
			phaseNum2++;
			phaseNum2Flag = true;
			phaseNum = 0;
		}

		if (enemyHP[19] <= 0)
		{
			scene = GameClearInit;
		}
		if (playerHP <= 0 || block.GetGameOverFlag() == true)
		{
			scene = GameOverInit;
		}
		//�p�[�e�B�N���X�V
		//particleMan->ParticleAdd(pPos1);
		particleMan->Update();
		//���C�g�X�V
		light->Update();
		break;
	case GameOverInit:
		scene = GameOver;
	case GameOver:
		if (input->KeybordTrigger(DIK_SPACE))
		{
			scene = TitleInit;
		}
		break;
	case GameClearInit:
		scene = GameClear;
	case GameClear:
		if (input->KeybordTrigger(DIK_SPACE))
		{
			scene = TitleInit;
		}
		break;
	}
	
}

void GameSceneManager::Draw(_DirectX directX)
{
	//�I�u�W�F�N�g�`��O����
	object->PreDraw();
	sprite->PreDraw();
	//��̕`��O�͓̂���Ȃ��Ă���
	//�V�[���Ǘ��̓y��
	switch (scene)
	{
	case TitleInit:
		scene = Title;
	case Title:
		sprite->Draw(titleGraph, XMFLOAT2(), 1920, 1080);
		break;
	case MainInit:
	case Main:
		//�w�i�`��
		sprite->Draw(BGGraph, XMFLOAT2{ 0.0f + shakeX,0.0f + shakeY }, window_width, window_height);
		sprite->Draw(BG2Graph, XMFLOAT2{ 0.0f + shakeX,0.0f + shakeY }, window_width, window_height);


		//�I�u�W�F�N�g
		//object->OBJDraw(Polygon, pPos1, XMFLOAT3{ 1.0f,1.0f,1.0f }, angle, XMFLOAT4{ 1.0f,1.0f,1.0f ,1.0f });
		//object->OBJDraw(Polygon, pPos2, XMFLOAT3{ 1.0f,1.0f,1.0f }, angle, XMFLOAT4{ 1.0f,1.0f,1.0f ,1.0f });


		table.Draw();

		block.Draw();

		//�G�̉摜
		if (nowPhase == 0 || nowPhase == 3 || nowPhase == 6 || nowPhase == 9 || nowPhase == 12 || nowPhase == 15 || nowPhase == 18)
		{ sprite->Draw(enemyGraph[0], XMFLOAT2(window_width / 2 - 133, 470), 250, 250); }
		if (nowPhase == 1 || nowPhase == 4 || nowPhase == 7 || nowPhase == 10 || nowPhase == 13 || nowPhase == 16 || nowPhase == 19) 
		{ sprite->Draw(enemyGraph[1], XMFLOAT2(window_width / 2 - 133, 470), 250, 250); }
		if (nowPhase == 2 || nowPhase == 5 || nowPhase == 8 || nowPhase == 11 || nowPhase == 14 || nowPhase == 17) 
		{ sprite->Draw(enemyGraph[2], XMFLOAT2(window_width / 2 - 133, 470), 250, 250); }
		//UI
		sprite->Draw(UIGraph, XMFLOAT2(), 1920, 1080);

		block.DrawUI();
		//�G�l�~�[�U���`��ꏊ
		if (eAttackFlag == true)
		{
			object->OBJDraw(Polygon, eAttackPos, XMFLOAT3{ 1.0f,1.0f,1.0f }, XMFLOAT3{});
		}

		
		//�p�[�e�B�N���`��
		particleMan->Draw();
		
		sprite->Draw(numGraph[playerHP], XMFLOAT2(1530,740), 128, 128);
		turnNum = enemyAttackDelay[nowPhase] - enemyAttackCount;
		sprite->Draw(numGraph[turnNum], XMFLOAT2(1530, 450), 128, 128);

		

		sprite->Draw(numGraph[phaseNum], XMFLOAT2(1680, 900), 128, 128);

		if (phaseNum2Flag == 1)
		{
			sprite->Draw(numGraph[phaseNum2], XMFLOAT2(1610, 900), 128, 128);
		}
		//�O�i�`��
		//sprite->Draw(spriteGraph, XMFLOAT2(0, 0), 100, 100);

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

		//debugText.Print(1600, 840, 5, "%d", playerHP);
		debugText.Print(10, 180, 2, "    enemyHP :%d", enemyHP[nowPhase]);
		//debugText.Print(1500, 980, 5, "      %d", nowPhase + 1);
		//debugText.Print(1600, 550, 5, "%d", enemyAttackDelay[nowPhase] - enemyAttackCount);
		debugText.Print(10, 300, 2, "         d  :%f", damage);
		//debugText.Print(10, 340, 2, "            :%d", block.GetSandDelay());
		//debugText.Print(10, 380, 2, "         d  :%f");
		//debugText.Print(10, 420, 2, "         d  :%f");
		//debugText.Print(10, 380, 2, "      combo :%d", block.GetComboCount());
		//debugText.Print(10, 420, 2, "    colorUp :%d", block.GetColorNumUp());
		//debugText.Print(10, 460, 2, "  colorDown :%d", block.GetColorNumDown());
		//debugText.Print(10, 500, 2, "  colorLeft :%d", block.GetColorNumLeft());
		//debugText.Print(10, 540, 2, " colorRight :%d", block.GetColorNumRight());
		//debugText.Print(10, 120, 2, "            :%d", block.GetSandDelay());
		debugText.Print(300, 840, 5, "      combo :%f", combo);
		debugText.Print(10, 200 + 0 * 40, 2, " color :%f ", damageUpValue[0]);
		debugText.Print(10, 200 + 1 * 40, 2, " color :%f ", damageUpValue[1]);
		debugText.Print(10, 200 + 2 * 40, 2, " color :%f ", damageUpValue[2]);
		debugText.Print(10, 200 + 3 * 40, 2, " color :%f ", damageUpValue[3]);
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
		//�f�o�b�N�e�L�X�g�`��

		break;
	case GameOverInit:
	case GameOver:
		sprite->Draw(GameOverGraph, XMFLOAT2(), 1920, 1080);
		break;
	case GameClearInit:
	case GameClear:
		break;
	}

	debugText.
		DrawAll();
}

void GameSceneManager::ColorDamageCheck()
{
	if (table.GetStatus() == UP)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
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

			///��2��
			if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Red) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownL[i] = damageLow; }
			if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownL[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = damageLow; }
			if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownL[i] = damageLow; }
			if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownL[i] = damageNormal; }
			if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownR[i] = damageLow; }
			if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///�E2��
			if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Red) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpR[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpR[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpR[i] = damageLow; }
			if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Red) { damageValueUpR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueUpR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueUpR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Red) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Blue) { damageValueDownR[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownR[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownR[i] = damageLow; }
			if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
		}
	}
	else if (table.GetStatus() == Down)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///��2��
			if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownL[i] = damageLow; }
			if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueDownL[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueDownL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueDownL[i] = damageLow; }
			if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///�E2��
			if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
		}
	}
	else if (table.GetStatus() == Left)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///�E2��
			if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
		}
	}
	else if (table.GetStatus() == Right)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorUp[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorUp[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///�E2��
			if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorDown[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorDown[i] == Blue) { damageValueDownR[i] = damageNormal; }


			///��2��
			if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomL[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Red && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Yellow && colorLeft[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorBottomR[nowPhase] == Blue && colorLeft[i] == Blue) { damageValueDownR[i] = damageNormal; }

			///��2��
			if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopL[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
			if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Red && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Red) { damageValueUpL[i] = damageNormal; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Yellow) { damageValueUpL[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Yellow && colorRight[i] == Blue) { damageValueUpL[i] = damagaHigh; }
			if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Red) { damageValueDownR[i] = damageLow; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Yellow) { damageValueDownR[i] = damagaHigh; }
			else if (enemyColorTopR[nowPhase] == Blue && colorRight[i] == Blue) { damageValueDownR[i] = damageNormal; }
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
float GameSceneManager::betaDamageValueCheck()
{
	for (int i = 0; i < block.GetComboCount(); i++)
	{
		damage = 5;
	}
	return damage;
}
void GameSceneManager::betaDamageCheck()
{
	if (enemyColor[nowPhase] == Red)
	{
		for (int i = 0; i < block.GetComboCount(); i++)
		{
			if (colorUp[i+1] == Red) { damageUpValue[i] = damageNormal; }
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
		for (int i = 0; i < block.GetComboCount(); i++)
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
		for (int i = 0; i < block.GetComboCount(); i++)
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
void GameSceneManager::ShakeUpdate()
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

void GameSceneManager::ShakeStart(float shakeTime, int shakeString)
{
	//�V�F�C�N���鎞��
	this->shakeTime = shakeTime;
	//�V�F�C�N�̋���
	this->shakeString = shakeString;
	//����
	shkeStringTime = shakeTime / 10;
	shakeFlag = false;
}
