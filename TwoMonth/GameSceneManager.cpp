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
	BGGraph = sprite->SpriteCreate(L"Resources/backgroundA.png");

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
}

void GameSceneManager::Update()
{
	if (input->KeybordPush(DIK_UP))
	{
		pPos1.z += 1;
	}
	if (input->KeybordPush(DIK_DOWN))
	{
		pPos1.z -= 1;
	}
	if (input->KeybordPush(DIK_LEFT))
	{
		pPos1.x -= 1;
	}
	if (input->KeybordPush(DIK_RIGHT))
	{
		pPos1.x += 1;
	}

	table.Update();

	block.Update();

	block.ColBlock(&table.table, table.GetPos(), table.GetStatus());
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
	//sprite->Draw(BGGraph, XMFLOAT2{ 0.0f,0.0f }, window_width, window_height);


	//オブジェクト
	//object->OBJDraw(Polygon, pPos1, XMFLOAT3{ 1.0f,1.0f,1.0f }, angle, XMFLOAT4{ 1.0f,1.0f,1.0f ,1.0f });
	//object->OBJDraw(Polygon, pPos2, XMFLOAT3{ 1.0f,1.0f,1.0f }, angle, XMFLOAT4{ 1.0f,1.0f,1.0f ,1.0f });


	table.Draw();

	block.Draw();

	//パーティクル描画
	particleMan->Draw();


	//前景描画
	//sprite->Draw(spriteGraph, XMFLOAT2(0, 0), 100, 100);

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

	//デバックテキスト描画
	debugText.DrawAll();
}
