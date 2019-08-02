#pragma once
#include <State.h>

class IdleState final: public dae::State
{
public:
	IdleState(dae::GameObject* pPlayer, dae::GameObject* pGrid);
	~IdleState();

private:
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pPlayerRef;
	dae::GameObject* m_pGridRef;
};

