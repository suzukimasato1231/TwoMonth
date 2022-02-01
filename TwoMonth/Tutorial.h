#pragma once
#include"2d/Sprite.h"
#include"Input/Input.h"
#include<time.h>
time_t time(time_t *);
extern const int window_width;
extern const int window_height;
enum TUTORIAL
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
};

class Tutorial
{
private:
	Input *input = nullptr;
	Sprite *sprite = nullptr;
public:
	Tutorial();
	~Tutorial();
	//������
	void Init(Input *input, Sprite *sprite);
	//���C��������
	void MainInit();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�`���[�g���A���t���O���l��
	bool GetTutorialFlag();
	//�`���[�g���A���t���O��false�ɂ���
	void TutorialFlagChange();
	//�`���[�g���A���̐������I��������ǂ����t���O���l��
	bool GetTutorialEndFlag();
	//�������ŃX�L�b�v
	bool Longpress();
	//���������ĂȂ�
	void NotLongpress();
private:
	//�`���[�g���A�������Ă��邩�ǂ���
	bool tutorialFlag = true;
	//�`���[�g���A���̐������I��������ǂ���
	bool tutorialEndFlag = false;

	Sprite::SpriteData Explanation1;//�����摜1
	Sprite::SpriteData Explanation2;//�����摜2
	Sprite::SpriteData Explanation3;//�����摜3
	Sprite::SpriteData Explanation4;//�����摜4
	Sprite::SpriteData Explanation5;//�����摜5
	Sprite::SpriteData Explanation6;//�����摜6
	Sprite::SpriteData Explanation7;//�����摜7
	Sprite::SpriteData Explanation8;//�����摜8


	Sprite::SpriteData numGraph[10];

	XMFLOAT2 position = { 0.0f, 180.0f };//���W

	//�`���[�g���A�����΂��{�^���̕\��
	Sprite::SpriteData SkipTutorialGraph;
	//�`���[�g���A�����̉��Ԗڂ�	
	int tutorialScene = ONE;
	//�`���[�g���A�����ς��ő厞��
	const int timeMax = 400;
	//���݂̃`���[�g���A���̎���
	int tutorialTime = 0;
	//���Ԍv��
	time_t start_time, end_time;
	bool timeFlag = false;

};