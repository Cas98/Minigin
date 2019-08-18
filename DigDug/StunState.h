#pragma once
#include <State.h>
class StunState final: public dae::State
{
public:
	StunState(dae::GameObject* pSnobee, dae::GameObject* pGrid, float stunTime);
	~StunState();

private:
	void Enter() override;
	void Exit() override;
	void Update() override;
	State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pSnobeeRef;
	dae::GameObject* m_pGridRef;
	float m_StunTime;
};

