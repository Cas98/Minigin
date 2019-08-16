#pragma once
#include <Scene.h>
#include "GridComponent.h"

class Level1 final: public dae::Scene
{
public:
	Level1();
	~Level1();

protected:
	virtual void Initialize() override;
	virtual void Update() override;
};

