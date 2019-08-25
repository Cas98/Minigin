#pragma once
#include <State.h>

class PushState final: public dae::State
{
public:
	PushState(dae::GameObject* pPlayer, dae::GameObject* pGrid);
	~PushState();

private:
	void Enter() {};
	void Exit() {};
	void Update() {};
	State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pPlayerRef;
	dae::GameObject* m_pGridRef;
};

