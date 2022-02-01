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
	//���f�[�^���
	Sound::SoundUnload(&soundDecision);
	Sound::SoundUnload(&block.Soundput);
	Sound::SoundUnload(&block.SoundSandwitch);
	Sound::SoundUnload(&table.SoundTable);
	Sound::SoundUnload(&enemy.Sounddamege);
	Sound::SoundUnload(&bgm);
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
	soundDecision = Sound::SoundLoadWave("Resources/Sound/Decision.wav");
	bgm = Sound::SoundLoadWave("Resources/Sound/BGM.wav");
	sound->SoundBGMPlayLoopWave(bgm, sound->BGM);

	//�J����
	view->SetViewCamera(XMFLOAT3{ 0,0,-1000 }, XMFLOAT3{ 0, 0, 0 }, XMFLOAT3{ 0, 1, 0 });

	//���C�g�F��ݒ�
	light->SetLightColor({ 1,1,1 });

	//�X�v���C�g�摜�ǂݍ���
	BGGraph = sprite->SpriteCreate(L"Resources/background.png");
	phaseGraph = sprite->SpriteCreate(L"Resources/phaseclear.png");
	UIGraph = sprite->SpriteCreate(L"Resources/UI1.png");
	GameOverGraph = sprite->SpriteCreate(L"Resources/gameover.png");
	titleGraph = sprite->SpriteCreate(L"Resources/title.png");
	spaceGraph = sprite->SpriteCreate(L"Resources/space.png");
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
	EnemyHpGraph = sprite->SpriteCreate(L"Resources/EnemyHP.png");
	EnemyHp2Graph = sprite->SpriteCreate(L"Resources/Hpbar.png");
	clearGraph = sprite->SpriteCreate(L"Resources/gameclear.png");

	playerHPGraph[0] = sprite->SpriteCreate(L"Resources/playerHP/playerlife4.png");
	playerHPGraph[1] = sprite->SpriteCreate(L"Resources/playerHP/playerlife3.png");
	playerHPGraph[2] = sprite->SpriteCreate(L"Resources/playerHP/playerlife2.png");
	playerHPGraph[3] = sprite->SpriteCreate(L"Resources/playerHP/playerlife1.png");

	//��N���X������
	table.Init(input, sprite, object,sound);
	//�u���b�N�N���X
	block.Init(input, sprite, object,sound);

	enemy.Init(sprite, object,sound);

	sceneChange.Init(sprite);

	tutorial.Init(input, sprite);

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
		titleTime = 0;
		enemy.MainInit();
		scene = Title;
	case Title:
		titleTime++;
		if (titleTime == 5000)
		{//�������𒴂��Ȃ��悤��
			titleTime = 0;
		}
		if (input->KeybordTrigger(DIK_SPACE))
		{
			sceneChange.Start();
			sound->SoundSEPlayWave(soundDecision);
		}
		if (sceneChange.Change())
		{
			scene = MainInit;
		}
		break;
	case MainInit:
		table.MainInit();
		block.MainInit();
		turnNum = 0;
		phaseNum = 0;			//�t�F�[�Y���P����
		phaseNum2Flag = false;	//�Q���ڂɓ�������
		phaseNum2 = 0;			//�t�F�[�Y���Q����
		playerHP = 3;///�̗�
		playerIsAlive = 1;///���݂��邩
		tutorial.MainInit();
		enemy.MainInit();
		scene = Main;
	case Main:
		table.ShakeGet(block.GetPutFlag());
#if _DEBUG
		if (input->KeybordPush(DIK_R))
		{
			table.MainInit();
			block.MainInit();
			//�v���C���[�X�e�[�^�X
			playerHP = 3;///�̗�
			playerIsAlive = true;///���݂��邩
			//�G�l�~�[
			enemy.MainInit();
		}
#endif
		if (enemy.GetphaseFlag() == false)
		{
			table.Update();

			block.Update(&table.table, table.GetStatus());

			block.ColBlock(&table.table, table.GetPos(), table.GetStatus());

			table.ShakeGet(block.GetShakeFlag());

			enemy.Update(playerHP, block.playerTimeFlag, block.GetComboCount()
				, block.GetPTime(), tutorial.GetTutorialFlag());

			if (block.playerTimeFlag && enemy.GeteAttackFlag() == false)
			{
				block.start_player = time(NULL);
				block.playerTimeFlag = false;
			}

			block.RockUpdate();
		}
		else
		{//�t�F�[�Y�N���A����U���������s������
			block.SandwitchDelete();
			table.ShakeGet(block.GetShakeFlag());
			table.ShakeStart(10.0f, 10);
			table.ShakeUpdate();
			block.RockUpdate();
		}
		enemy.PhaseUpdate(block.GetCheckFlag(), block.GetSandEndFlag(), block.GetComboCount(),
			block.GetColorNumUp(), block.GetColorNumDown(), block.GetColorNumLeft(), block.GetColorNumRight(), table.GetStatus());
		//�t�F�[�Y�N���A�C�[�W���O
		if (enemy.GetphaseFlag() == true)
		{
			sceneChange.phaseEasingStart(XMFLOAT3{ 0.0f,-200.0f,0.0f }, XMFLOAT3{ 0.0f,0.0f,0.0f }, 100);
		}
		else
		{
			sceneChange.ChangePhaseFlag();
		}
		if (enemy.GetPhaseDelay() > 120)
		{
			block.DeleteBlock();
			phaseNum++;
			enemy.FlagChenge();
		}

		tutorial.Update();
		if ((input->KeybordPush(DIK_E) || tutorial.GetTutorialEndFlag()) && tutorial.GetTutorialFlag() == true)
		{//�`���[�g���A���𔲂���
			if (tutorial.Longpress() == true || tutorial.GetTutorialEndFlag())
			{//�Q�b������������V�[���`�F���W�X�^�[�g
				sceneChange.Start();
			}
		}
		else
		{
			tutorial.NotLongpress();
		}
		if (sceneChange.Change())
		{//�`���[�g���A�����烁�C���ւ̃V�[���`�F���W�i���o�j
			phaseNum++;
			enemy.FlagChenge();
			tutorial.TutorialFlagChange();
			block.DeleteBlock();
			block.ChangeGameOverFlag();
		}

		//�`���[�g���A�����ɃQ�[���I�[�o�[�ɂȂ�Ȃ��悤�ɂ���
		if (tutorial.GetTutorialFlag() == true)
		{
			playerHP = 3;

			block.ChangeGameOverFlag();
		}

		if (input->KeybordPush(DIK_B))
		{
			input->KeybordPush(DIK_B);
		}

		//�t�F�[�Y�񌅖ڂ̐����X�V
		if (phaseNum == 10)
		{
			phaseNum2++;
			phaseNum2Flag = true;
			phaseNum = 0;
		}
		//�^�[�������X�V
		turnNum = enemy.GetAttackDelay() - enemy.GetAttackCount();
		particleMan->PowerUpParticleAdd({ 0,0,0 }, enemy.GetCombo(), enemy.GetEnemyDeadFlag() == true);
		if (enemy.GetEnemyDeadFlag() == true && particleTime < 60)
		{
			particleTime++;
			for (int i = 0; i < 4; i++)
			{
				if (enemy.GetEnemyColor(i) == Red) {
					particleMan->EnemyRParticleAdd({ 0,0,-50 }); }
				if (enemy.GetEnemyColor(i) == Yellow) { 
					particleMan->EnemyGParticleAdd({ 0,0,-50 }); }
				if (enemy.GetEnemyColor(i) == Blue) { 
					particleMan->EnemyBParticleAdd({ 0,0,-50 }); }
			}
		}
		else if (enemy.GetEnemyDeadFlag() == false)
		{
			particleTime = 0;
		}

		if (enemy.GetEnemyLastHP() <= 0 && enemy.GetPhaseDelay() > 120)
		{
			scene = GameClearInit;
		}
		if (playerHP <= 0 || block.GetGameOverFlag() == true)
		{
			scene = GameOverInit;
		}
		hpRatio = enemy.GetEnemyHP() / enemy.GetConstEnemyHP();
		if (hpRatio < 0)
		{
			hpRatio = 0.0f;
		}
		//�p�[�e�B�N���X�V
		//particleMan->ParticleAdd(pPos1);
		particleMan->Update();
		//���C�g�X�V
		light->Update();
		break;
	case GameOverInit:
		sceneChange.gameoverasingStart(XMFLOAT3(0.0f, -window_height, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 100);
		sceneChange.ChangePhasegameoverFlag();
		scene = GameOver;
	case GameOver:
		if (input->KeybordTrigger(DIK_SPACE))
		{
			sceneChange.Start();
			sound->SoundSEPlayWave(soundDecision);
		}
		if (sceneChange.Change())
		{
			scene = TitleInit;
		}
		break;
	case GameClearInit:
		table.MainInit();
		block.MainInit();
		//�v���C���[�X�e�[�^�X
		playerHP = 3;///�̗�
		playerIsAlive = 1;///���݂��邩

		enemy.MainInit();
		scene = GameClear;
	case GameClear:
		if (input->KeybordTrigger(DIK_SPACE))
		{
			sceneChange.Start();
			sound->SoundSEPlayWave(soundDecision);
		}
		if (sceneChange.Change())
		{
			scene = TitleInit;
		}
		break;
	}
	sceneChange.Update();
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
		sprite->Draw(titleGraph, XMFLOAT2(), window_width, window_height);
		if (titleTime % 60 >= 25)
		{
			sprite->Draw(spaceGraph, XMFLOAT2(), window_width, window_height);
		}
		break;
	case MainInit:
	case Main:
	case GameOverInit:
	case GameOver:
		//�w�i�`��
		sprite->Draw(BGGraph, XMFLOAT2{ 0.0f + enemy.GetShakePos().x,0.0f + enemy.GetShakePos().y }, window_width, window_height);
		//�u���b�N�ő吔������
		block.WallningDraw();
		//��̕`��
		table.Draw();


		//�G�̉摜
		enemy.Draw();
		//�u���b�N�̕`��
		block.Draw();
		block.RockDraw();
		//UI
		sprite->Draw(UIGraph, XMFLOAT2(), 1920, 1080);


		//�G�̍U���`��
		enemy.AttackDraw();


		//�p�[�e�B�N���`��
		particleMan->Draw();
		//�_���[�W�\��
		enemy.DrawDamege();
		//UI�`��
		block.DrawUI();
		//�Q�[���I�[�o�[�܂ł̃J�E���g�`��
		block.DrawGameOverCount();
		//�v���C���[HP
		sprite->Draw(playerHPGraph[playerHP], XMFLOAT2(), window_width, window_height);
		sprite->Draw(numGraph[turnNum], XMFLOAT2(230, 340), 128, 128);

		sprite->Draw(numGraph[block.GetPTime()], XMFLOAT2(390, 340), 128, 128);

		sprite->Draw(numGraph[phaseNum], XMFLOAT2(1710, 580), 128, 128);
		if (phaseNum2Flag == TRUE)
		{
			sprite->Draw(numGraph[phaseNum2], XMFLOAT2(1640, 580), 128, 128);
		}

		if (enemy.GetphaseFlag() == TRUE)
		{
			sceneChange.DrawPhase();
		}


		//�GHP�Q�[�W
		if (enemy.GetEnemyHP() >= 0)
		{
			sprite->Draw(EnemyHpGraph, XMFLOAT2(130, 730), 330 * hpRatio, 40);
		}
		sprite->Draw(EnemyHp2Graph, XMFLOAT2(129, 730), 332, 40);
		//�R���{�I���܂ł̃Q�[�W
		//sprite->Draw(EnemyHpGraph, XMFLOAT2(620, 600), block.GetSandDelay(), 20);
		tutorial.Draw();
#if _DEBUG
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
		debugText.Print(1, 200, 2, "playerTime:%d", block.GetPTime());
		debugText.Print(1, 30, 2, "AD:rotation");
		debugText.Print(1, 60, 2, "yazirusi:position");
		//debugText.Print(1600, 550, 5, "%d", enemyAttackDelay[nowPhase] - enemyAttackCount);
		//debugText.Print(10, 300, 2, "         d  :%f", damage);
		//debugText.Print(10, 340, 2, "            :%d", block.GetSandDelay());
		//debugText.Print(10, 380, 2, "         d  :%f");
		debugText.Print(10, 420, 2, "         HP  :%f",enemy.GetEnemyHP());
		//debugText.Print(10, 380, 2, "      comboa :%f", a);
		//debugText.Print(10, 420, 2, "    colorUp :%d", block.GetColorNumUp());
		//debugText.Print(10, 460, 2, "  colorDown :%d", block.GetColorNumDown());
		//debugText.Print(10, 500, 2, "  colorLeft :%d", block.GetColorNumLeft());
		//debugText.Print(10, 540, 2, " colorRight :%d", block.GetColorNumRight());
		//debugText.Print(10, 120, 2, "            :%d", block.GetSandDelay());
		debugText.Print(300, 840, 5, "      combo :%d", enemy.GetCombo());
		debugText.Print(10, 200 + 0 * 40, 2, " color :%d %d %d %d", enemy.GetDamegeValue(0, 0), enemy.GetDamegeValue(0, 1), enemy.GetDamegeValue(0, 2), enemy.GetDamegeValue(0, 3));
		debugText.Print(10, 200 + 1 * 40, 2, " color :%d %d %d %d", enemy.GetDamegeValue(1, 0), enemy.GetDamegeValue(1, 1), enemy.GetDamegeValue(1, 2), enemy.GetDamegeValue(1, 3));
		debugText.Print(10, 200 + 2 * 40, 2, " color :%d %d %d %d", enemy.GetDamegeValue(2, 0), enemy.GetDamegeValue(2, 1), enemy.GetDamegeValue(2, 2), enemy.GetDamegeValue(2, 3));
		debugText.Print(10, 200 + 3 * 40, 2, " color :%d %d %d %d", enemy.GetDamegeValue(3, 0), enemy.GetDamegeValue(3, 1), enemy.GetDamegeValue(3, 2), enemy.GetDamegeValue(3, 3));
		/*	debugText.Print(10, 200 + 0 * 40, 2, " color :%f ", damageUpValue[0]);
			debugText.Print(10, 200 + 1 * 40, 2, " color :%f ", damageUpValue[1]);
			debugText.Print(10, 200 + 2 * 40, 2, " color :%f ", damageUpValue[2]);
			debugText.Print(10, 200 + 3 * 40, 2, " color :%f ", damageUpValue[3]);*/
			//debugText.Print(10, 200 + 4 * 40, 2, " color :%d %d %d %d", colorUp[4], colorDown[4], colorLeft[4], colorRight[4]);
			//debugText.Print(10, 200 + 5 * 40, 2, " color :%d %d %d %d", colorUp[5], colorDown[5], colorLeft[5], colorRight[5]);
			//debugText.Print(10, 200 + 6 * 40, 2, " color :%d %d %d %d", colorUp[6], colorDown[6], colorLeft[6], colorRight[6]);
			//debugText.Print(10, 200 + 7 * 40, 2, " color :%d %d %d %d", colorUp[7], colorDown[7], colorLeft[7], colorRight[7]);
			//debugText.Print(10, 200 + 8 * 40, 2, " color :%d %d %d %d", colorUp[8], colorDown[8], colorLeft[8], colorRight[8]);
			//debugText.Print(10, 200 + 9 * 40, 2, " color :%d %d %d %d", colorUp[9], colorDown[9], colorLeft[9], colorRight[9]);
			//debugText.Print(10, 200 + 10 * 40, 2, " color :%d %d %d %d", colorUp[10], colorDown[10], colorLeft[10], colorRight[10]);
			//�f�o�b�N�e�L�X�g�`��
#endif
		if (scene == GameOver)
		{
			sceneChange.DrawGameOver();
		}
		break;
	case GameClearInit:
	case GameClear:
		sprite->Draw(clearGraph, XMFLOAT2(), window_width, window_height);
		break;
	}
	//�V�[���`�F���W�̍��`��
	sceneChange.Draw();
	debugText.
		DrawAll();
}

