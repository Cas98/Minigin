#pragma once
#include <State.h>
#include "helpers.h"

class MoveState final: public dae::State
{
public:
	MoveState(dae::GameObject* pPlayer, dae::GameObject* pGrid, Direction dir, float speed);
	~MoveState();

private:
	void Enter();
	void Exit();
	void Update();
	State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pPlayerRef;
	dae::GameObject* m_pGridRef;

	glm::vec2 m_DirectionCoord;
	Direction m_Direction;
	bool m_ChangeState = false;
	float m_Offset;
	float m_Speed = 128.0f;
};


