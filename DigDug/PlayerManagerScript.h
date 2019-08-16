#pragma once
#include <ScriptComponent.h>
#include "GameObject.h"

class PlayerManagerScript : public dae::ScriptComponent
{
public:
	PlayerManagerScript(dae::GameObject* pGrid);
	~PlayerManagerScript();

	virtual void Init() override;
	virtual void Update() override;

	void RespawnPlayer();

private:
	int m_PlayerLives = 4;
	dae::GameObject* m_pGrid;
	std::vector<dae::GameObject*> m_pLifeUIs;

};

