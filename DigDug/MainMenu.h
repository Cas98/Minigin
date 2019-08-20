#pragma once
#include <Scene.h>
class MainMenu final: public dae::Scene
{
public:
	MainMenu();
	~MainMenu();

private:
	virtual void Initialize() override;
	virtual void Update() override;
};

