#pragma once
#include <ScriptComponent.h>
class LevelLoaderScript final: public dae::ScriptComponent
{
public:
	LevelLoaderScript();
	~LevelLoaderScript();

	virtual void Init() override;
	virtual void Update() override;

	void Load(const std::vector<int>& map);

private:
	void AddWall(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore, bool canSpawnSnobee = false);
	//void AddSnobee(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager);
	void AddDiamond(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore);
};

