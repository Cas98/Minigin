#pragma once
#include <ScriptComponent.h>
#include "InputComponent.h"
#include "Observer.h"
#include "helpers.h"
#include "PlayerManagerScript.h"
#include "ScoreScript.h"

class GameScript final: public dae::ScriptComponent, public dae::Observer
{
public:
	GameScript(int nextLevel, GameMode gameMode, dae::GameObject* pPlayerManager, dae::GameObject* pScore);
	~GameScript();

private:
	virtual void Init() override;
	virtual void Update() override;

	void EndGame();

	dae::InputComponent* m_pInputRef;

	void OnNotify(dae::GameObject* gameObject, const std::string& message) override;
	int m_Nextlevel;
	GameMode m_GameMode;
	PlayerManagerScript* m_pPlayerManagerRef;
	ScoreScript* m_pScore;

	float m_Time = 60.0f;
};

