#include "SceneChange.h"

void SceneChange::Init(Sprite *sprite)
{
	this->sprite = sprite;
	SceneGraph = sprite->SpriteCreate(L"Resources/SceneChange.png");
	phaseClearGraph = sprite->SpriteCreate(L"Resources/phaseclear.png");
	gameOverGraph = sprite->SpriteCreate(L"Resources/gameover.png");
}

SceneChange::XMFLOAT4 SceneChange::GetColor()
{
	return changeColor;
}

bool SceneChange::GetChangeFlag()
{
	return sceneChangeFlag;
}

bool SceneChange::Change()
{
	return changeColor.w >= 1.0f;
}

void SceneChange::Start()
{
	if (sceneChangeFlag == false)
	{
		sceneChangeFlag = true;
		firstHalfFlag = true;
		changeColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void SceneChange::Update()
{
	if (sceneChangeFlag == true)
	{
		const float changeSpeed = 0.045f;
		if (firstHalfFlag == true)
		{
			changeColor.w += changeSpeed;
			if (changeColor.w >= 1.0f)
			{
				firstHalfFlag = false;
			}
		}
		else
		{
			if (changeColor.w <= 0.0f)
			{
				sceneChangeFlag = false;
			}
			changeColor.w -= changeSpeed;
		}
	}
}

void SceneChange::Draw()
{
	if (GetChangeFlag() == true)
	{
		sprite->Draw(SceneGraph, XMFLOAT2(0.0f, 0.0f), window_width, window_height, XMFLOAT2{ 0.0f,0.0f }, changeColor);
	}
}
void SceneChange::phaseEasingStart(XMFLOAT3 start, XMFLOAT3 end, float time)
{
	if (phaseFlag == true)
	{
		phaseFlag = false;
		this->phaseStart = XMFLOAT3(start.x, start.y, start.z);
		this->phaseEnd = XMFLOAT3(end.x, end.y, end.z);
		this->phaseMaxTime = time;
		phaseEasingTime = 0;
	}
}
XMFLOAT3 SceneChange::phaseEasing()
{
	phaseEasingTime++;

	phaseTimeRate = min(phaseEasingTime / phaseMaxTime, 1.0f);
	XMFLOAT3 position;

	position = easeOut(phaseStart, phaseEnd, phaseTimeRate);

	return XMFLOAT3(position.x, position.y, position.z);
}

void SceneChange::ChangePhaseFlag()
{
	phaseFlag = true;
}
void SceneChange::DrawPhase()
{
	XMFLOAT3 pos = phaseEasing();
	sprite->Draw(phaseClearGraph, XMFLOAT2(pos.x, pos.y), window_width, window_height);
}

void SceneChange::gameoverasingStart(XMFLOAT3 start, XMFLOAT3 end, float time)
{
	if (gameoverFlag == true)
	{
		gameoverFlag = false;
		this->phaseStart = XMFLOAT3(start.x, start.y, start.z);
		this->phaseEnd = XMFLOAT3(end.x, end.y, end.z);
		this->phaseMaxTime = time;
		phaseEasingTime = 0;
	}
}

XMFLOAT3 SceneChange::gameoverEasing()
{
	phaseEasingTime++;

	phaseTimeRate = min(phaseEasingTime / phaseMaxTime, 1.0f);
	XMFLOAT3 position;

	position = easeOut(phaseStart, phaseEnd, phaseTimeRate);

	return XMFLOAT3(position.x, position.y, position.z);
}

void SceneChange::ChangePhasegameoverFlag()
{
	gameoverFlag = true;
}

void SceneChange::DrawGameOver()
{
	XMFLOAT3 pos = phaseEasing();
	sprite->Draw(gameOverGraph, XMFLOAT2(pos.x, pos.y), window_width, window_height);
}


const  XMFLOAT3 lerp(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t)
{
	return start * (1.0f - t) + end * t;
}

const XMFLOAT3 easeIn(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t)
{
	float y = t * t;
	return start * (1.0f - y) + end * y;

}

const XMFLOAT3 easeOut(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t)
{
	float y = t * (2 - t);
	return start * (1.0f - y) + end * y;
}

const XMFLOAT3 easeInOut(const XMFLOAT3 &start, const XMFLOAT3 &end, const float t)
{
	float y = t * t * (3 - 2 * t);
	return start * (1.0f - y) + end * y;
}