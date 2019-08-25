#pragma once
#include <State.h>
#include "helpers.h"

class PushedState final: public dae::State
{
public:
	PushedState(dae::GameObject* pBlock, dae::GameObject* pGrid, Direction direction, bool firstMove);
	~PushedState();

private:
	void Enter(){};
	void Exit(){};
	void Update(){};
	State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pBlockRef;
	dae::GameObject* m_pGridRef;
	Direction m_Direction;

	bool m_FirstMove;

};

