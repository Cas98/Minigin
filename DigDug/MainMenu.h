#pragma once
#include <Scene.h>
#include "GameObject.h"

class MainMenu final: public dae::Scene
{
public:
	MainMenu();
	~MainMenu();

	void SetScore(int score);

private:
	virtual void Initialize() override;
	virtual void Update() override;

	int m_Score = 0;

	bool m_NeedsUpdate = false;
	dae::GameObject* m_pScore;
};

