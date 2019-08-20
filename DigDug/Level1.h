#pragma once
#include <Scene.h>
#include "GridComponent.h"
#include "helpers.h"

class Level1 final: public dae::Scene
{
public:
	Level1(GameMode gameMode);
	~Level1();


private:
	virtual void Initialize() override;
	virtual void Update() override;

	GameMode m_GameMode;
};

