#pragma once
#include "base/_DirectX.h"
#include "base/Safe_delete.h"
#include "Input/Input.h"
#include"2d/DebugText.h"
#include "3d/Object.h"
#include"3d/ParticleManager.h"
#include"Collision/Collision.h"
#include"Sound/Sound.h"
#include"Table.h"
#include"Block.h"
#include"Enemy.h"
#include"SceneChange.h"
#include"Tutorial.h"
extern const int window_width;
extern const int window_height;

enum Scene
{
	TitleInit,
	Title,
	MainInit,
	Main,
	GameOverInit,
	GameOver,
	GameClearInit,
	GameClear,
};

class GameSceneManager
{
private:
	Input *input = nullptr;
	_DirectX *directX = nullptr;
public:
	GameSceneManager();
	~GameSceneManager();

	void Initialize(Input *input, _DirectX *directX);

	void Init();

	void Update();

	void Draw(_DirectX directX);
private:
	Object *object = nullptr;
	Sprite *sprite = nullptr;
	ParticleManager *particleMan = nullptr;
	View *view = nullptr;
	Light *light = nullptr;
	DebugText debugText;
	Sound *sound = nullptr;
private://��`

	//���f�[�^
	Sound::SoundData soundDecision;//���艹
	Sound::SoundData sound2;

	//�X�v���C�g�摜
	Sprite::SpriteData spriteGraph;
	Sprite::SpriteData BGGraph;

	Sprite::SpriteData phaseGraph;//�t�F�[�Y�摜
	Sprite::SpriteData titleGraph;//�^�C�g���摜
	Sprite::SpriteData spaceGraph;//�^�C�g���̃X�y�[�X
	Sprite::SpriteData GameOverGraph;//�Q�[���I�[�o�[�摜
	Sprite::SpriteData clearGraph;//�N���A�摜
	Sprite::SpriteData numGraph[10];///�����摜
	Sprite::SpriteData EnemyHpGraph;///�����摜

	Sprite::SpriteData UIGraph;//UI�摜
	Sprite::SpriteData playerHPGraph[4];//�v���C���[HP
	//��N���X
	Table table;

	//�u���b�N�N���X
	Block block;

	//�G
	Enemy enemy;
	//�V�[���`�F���W�N���X
	SceneChange sceneChange;
	//�`���[�g���A���N���X
	Tutorial tutorial;
	//�v���C���[�X�e�[�^�X
	int playerHP = 3;///�̗�
	bool playerIsAlive = 1;///���݂��邩

	int scene = TitleInit;
	int turnNum = 0;
	int phaseNum = 0;			//�t�F�[�Y���P����
	bool phaseNum2Flag = false;	//�Q���ڂɓ�������
	int phaseNum2 = 0;			//�t�F�[�Y���Q����

	float hpRatio = 0;

	int titleTime = 0;//�X�y�[�X�{�^����_�ł����邽�߂̎���
};