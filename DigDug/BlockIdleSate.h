#pragma once
#include <State.h>
#include "Observer.h"

class BlockIdleSate final: public dae::State , public Observer
{
public:
	BlockIdleSate(dae::GameObject* pBlock, dae::GameObject* pGrid);
	~BlockIdleSate() = default;

protected:
	void OnNotify(std::string message) override;

private:
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual State* HandleInput(dae::InputComponent* input);

	dae::GameObject* m_pBlockRef;
	dae::GameObject* m_pGridRef;

	bool m_Move = false;
};

