#pragma once
#include <State.h>
#include "Observer.h"

class SnobeeIdleState final: public dae::State
{
public:
	SnobeeIdleState(dae::GameObject* pSnobee, dae::GameObject* pGrid);
	~SnobeeIdleState();

	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pSnobeeRef;
	dae::GameObject* m_pGridRef;
};

