#pragma once
#include <Scene.h>
#include "helpers.h"

class Level3 final: public dae::Scene
{
public:
	Level3(GameMode gameMode, int playerLives, int score);
	~Level3();

private:
	virtual void Initialize() override;
	virtual void Update() override;

	GameMode m_GameMode;
	int m_PlayerLives;
	int m_Score;
};

