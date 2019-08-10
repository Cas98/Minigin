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
private:
	void AddWall(int x, int y, dae::GameObject* pGrid);
	void AddSnobee(int x, int y, dae::GameObject* pGrid);
	void AddDiamond(int x, int y, dae::GameObject* pGrid);
};

