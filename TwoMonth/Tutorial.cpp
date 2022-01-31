#include "Tutorial.h"

Tutorial::Tutorial() {}

Tutorial::~Tutorial() {}

void Tutorial::Init(Input *input, Sprite *sprite)
{
	assert(input);
	this->input = input;
	assert(sprite);
	this->sprite = sprite;

	//チュートリアルの画像を読み込み
	Explanation1 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial01.png");
	Explanation2 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial02.png");
	Explanation3 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial03.png");
	Explanation4 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial04.png");
	Explanation5 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial5.png");
	Explanation6 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial6.png");
	Explanation7 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial7.png");
	Explanation8 = this->sprite->SpriteCreate(L"Resources/tutorial/tutorial8.png");


	//SkipTutorialGraph = this->sprite->SpriteCreate(L"");
	tutorialFlag = true;	//チュートリアルをしているかどうか
	tutorialScene = ONE;	//チュートリアル説明最初
	timeFlag = false;		//時間フラグ初期化
	tutorialEndFlag = false;
	tutorialTime = timeMax;
}

void Tutorial::MainInit()
{
	tutorialFlag = true;	//チュートリアルをしているかどうか
	tutorialScene = ONE;	//チュートリアル説明最初
	timeFlag = false;		//時間フラグ初期化
	tutorialEndFlag = false;
	tutorialTime = timeMax;
}

void Tutorial::Update()
{
	//チュートリアル中だったら
	if (tutorialFlag == true)
	{
		tutorialTime--;
		switch (tutorialScene)
		{
		case ONE:
			if (tutorialTime <= 0)
			{
				tutorialScene = TWO;
				tutorialTime = timeMax;
			}
			break;
		case TWO:
			if (tutorialTime <= 0)
			{
				tutorialScene = THREE;
				tutorialTime = timeMax;
			}
			break;
		case THREE:
			if (tutorialTime + 50 <= 0)
			{
				tutorialScene = FOUR;
				tutorialTime = timeMax;
			}
			break;
		case FOUR:
			if (tutorialTime + 50 <= 0)
			{
				tutorialScene = FIVE;
				tutorialTime = timeMax;
			}
			break;
		case FIVE:
			if (tutorialTime + 50 <= 0)
			{
				tutorialScene = SIX;
				tutorialTime = timeMax;
			}
			break;
		case SIX:
			if (tutorialTime + 50 <= 0)
			{
				tutorialScene = SEVEN;
				tutorialTime = timeMax;
			}
			break;
		case SEVEN:
			if (tutorialTime + 100 <= 0)
			{
				tutorialScene = EIGHT;
				tutorialTime = timeMax;
			}
			break;
		case EIGHT:
			if (tutorialTime <= 0)
			{
				tutorialScene = NINE;
				tutorialTime = timeMax;
			}
			break;

		case NINE:
			if (tutorialTime - 300 <= 0)
			{
				tutorialEndFlag = true;
			}
			break;
		}
	}
}

void Tutorial::Draw()
{	//チュートリアル中だったら
	if (tutorialFlag == true)
	{
		//チュートリアルを飛ばすボタン表示
		//sprite->Draw(SkipTutorialGraph,XMFLOAT2(),100.0f,100.0f);
		switch (tutorialScene)
		{
		case ONE:
			sprite->Draw(Explanation1, position, window_width, window_height);
			break;
		case TWO:
			sprite->Draw(Explanation2, position, window_width, window_height);
			break;
		case THREE:
			sprite->Draw(Explanation3, position, window_width, window_height);
			break;
		case FOUR:
			sprite->Draw(Explanation4, position, window_width, window_height);
			break;
		case FIVE:
			sprite->Draw(Explanation5, position, window_width, window_height);
			break;
		case SIX:
			sprite->Draw(Explanation6, position, window_width, window_height);
			break;
		case SEVEN:
			sprite->Draw(Explanation7, position, window_width, window_height);
			break;
		case EIGHT:
			sprite->Draw(Explanation8, position, window_width, window_height);
			break;
		}
	}
}

bool Tutorial::GetTutorialFlag()
{
	return tutorialFlag;
}

void Tutorial::TutorialFlagChange()
{
	tutorialFlag = false;
}

bool Tutorial::GetTutorialEndFlag()
{
	return tutorialEndFlag;
}

bool Tutorial::Longpress()
{
	if (timeFlag == false)
	{
		timeFlag = true;
		start_time = time(NULL);
		return false;
	}
	else
	{
		end_time = time(NULL);

		if (end_time - start_time > 2)
		{
			return true;
		}

		return false;
	}
}

void Tutorial::NotLongpress()
{
	timeFlag = false;
}
