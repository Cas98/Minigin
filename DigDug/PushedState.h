#pragma once
#include <State.h>
#include "helpers.h"

class PushedState : public dae::State
{
public:
	PushedState(dae::GameObject* pBlock, dae::GameObject* pGrid, dae::Direction direction, bool firstMove);
	~PushedState();

private:
	void Enter(){};
	void Exit(){};
	void Update(){};
	State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pBlockRef;
	dae::GameObject* m_pGridRef;
	dae::Direction m_Direction;

	bool m_FirstMove;

};

