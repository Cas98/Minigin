#pragma once
#include <Scene.h>
#include "helpers.h"

class Level2 final: public dae::Scene
{
public:
	Level2(GameMode gameMode);
	~Level2();

private:
	virtual void Initialize() override;
	virtual void Update() override;

	GameMode m_GameMode;
};

