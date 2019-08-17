#pragma once
#include <Scene.h>
#include "GridComponent.h"

class Level1 final: public dae::Scene
{
public:
	Level1();
	~Level1();

	float sec = 10.0f;

protected:
	virtual void Initialize() override;
	virtual void Update() override;

	
};

