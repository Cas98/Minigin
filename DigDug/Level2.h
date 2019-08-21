#pragma once
#include <Scene.h>
#include "helpers.h"

class Level2 final: public dae::Scene
{
public:
	Level2(GameMode gameMode, int playerLives, int score);
	~Level2();

private:
	virtual void Initialize() override;
	virtual void Update() override;

	GameMode m_GameMode;
	int m_PlayerLives;
	int m_Score;
};

