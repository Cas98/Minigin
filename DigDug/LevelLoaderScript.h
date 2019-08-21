#pragma once
#include <ScriptComponent.h>
#include "GameScript.h"

class LevelLoaderScript final: public dae::ScriptComponent
{
public:
	LevelLoaderScript(int nextLevel, GameMode gameMode, int playerLives, int score);
	~LevelLoaderScript();

	void Load(const std::vector<int>& map);

private:
	virtual void Init() override;
	virtual void Update() override;

	void AddWall(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore, bool canSpawnSnobee = false, bool isSnobeeAi = true);
	//void AddSnobee(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager);
	void AddDiamond(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore);
	void AddPlayer(int x, int y, dae::GameObject* pGrid, dae::GameObject* pPlayerManager, dae::GameObject* pScore, int playerIndex);

	int m_NextLevel;
	int m_PlayerLives;
	GameMode m_GameMode;
	int m_Score;
};


