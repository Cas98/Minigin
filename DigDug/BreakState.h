#pragma once
#include <State.h>
class BreakState : public dae::State
{
public:
	BreakState(dae::GameObject* pBlock);
	~BreakState() = default;

private:
	void Enter();
	void Exit() {};
	void Update() {};
	State* HandleInput(dae::InputComponent* input) { return nullptr; };

	dae::GameObject* m_pBlockRef;
};

