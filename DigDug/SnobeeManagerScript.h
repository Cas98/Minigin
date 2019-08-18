#pragma once
#include "ScriptComponent.h"
#include "GridComponent.h"
class SnobeeScript;

class SnobeeManagerScript final: public dae::ScriptComponent
{
public:
	SnobeeManagerScript(dae::GameObject* pGrid);
	~SnobeeManagerScript();

	virtual void Init() override;
	virtual void Update() override;

	void AddWall(dae::GameObject* pWall);
	void RemoveWall(dae::GameObject* pWall);

	void DecrementActiveSnobees();
	void StunSnobees();
	void RemoveObserver(SnobeeScript* pSnobeeObserver);

private:
	std::vector<dae::GameObject*> m_pWallsThatSpawnSnobees;
	int m_NumberOfActiveSnobees = 0;
	const int m_MaxActiveSnobees = 3;

	dae::GridComponent* m_pGridCompRef;
	void SpawnSnobee(int x, int y);
	std::vector<dae::GameObject*> m_pLifeUIs;
};

