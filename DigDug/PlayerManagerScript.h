#pragma once
#include <ScriptComponent.h>
#include "GameObject.h"

class PlayerManagerScript : public dae::ScriptComponent
{
public:
	PlayerManagerScript(dae::GameObject* pGrid, int lives);
	~PlayerManagerScript();

	virtual void Init() override;
	virtual void Update() override;

	void RespawnPlayer(int x, int y, int playerIndex);
	int GetPlayerLives() const;

private:
	int m_PlayerLives;
	dae::GameObject* m_pGrid;
	std::vector<dae::GameObject*> m_pLifeUIs;

};

