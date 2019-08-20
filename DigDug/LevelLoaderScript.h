#pragma once
#include <ScriptComponent.h>
class LevelLoaderScript final: public dae::ScriptComponent
{
public:
	LevelLoaderScript();
	~LevelLoaderScript();

	void Load(const std::vector<int>& map);

private:
	virtual void Init() override;
	virtual void Update() override;

	void AddWall(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore, bool canSpawnSnobee = false, bool isSnobeeAi = true);
	//void AddSnobee(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager);
	void AddDiamond(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore);
	void AddPlayer(int x, int y, dae::GameObject* pGrid, dae::GameObject* pPlayerManager, dae::GameObject* pScore, int playerIndex);
};


