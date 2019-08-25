#pragma once
#include <State.h>
#include "BlockScript.h"

class BlockIdleSate final: public dae::State
{
public:
	BlockIdleSate(dae::GameObject* pBlock, dae::GameObject* pGrid);
	~BlockIdleSate() = default;

private:
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pBlockRef;
	dae::GameObject* m_pGridRef;
	BlockScript* m_pBlockScriptRef;

	bool m_Move = false;
};

