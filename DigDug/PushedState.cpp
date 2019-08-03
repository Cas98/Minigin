#include "pch.h"
#include "PushedState.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "BlockIdleSate.h"
#include "MoveState.h"
#include "BreakState.h"

PushedState::PushedState(dae::GameObject* pBlock, dae::GameObject* pGrid, dae::Direction direction, bool firstMove)
	:m_pBlockRef(pBlock), m_pGridRef(pGrid), m_Direction(direction), m_FirstMove(firstMove)
{
}


PushedState::~PushedState()
{
}


dae::State* PushedState::HandleInput(dae::InputComponent* )
{
	//get target position

	auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
	glm::vec2 coords = gridcomp->GetGameObjectPos(m_pBlockRef);

	switch(m_Direction)
	{
	case dae::Direction::Down:
		coords.y -= 1;
		break;
	case dae::Direction::Up:
		coords.y += 1;
		break;
	case dae::Direction::Left:
		coords.x -= 1;
		break;
	case dae::Direction::Right:
		coords.x += 1;
		break;
	}

	int height = gridcomp->GetHeight();
	int width = gridcomp->GetWidth();

	auto targetObj = gridcomp->GetGameObject(int(coords.x), int(coords.y));

	bool isBlocked = false;

	if(targetObj)
	{
		if(targetObj->GetTag() == "Wall")
		{
			isBlocked = true;
		}
	}

	if(coords.x < 0 || coords.x >= width || coords.y < 0 || coords.y >= height || isBlocked)
	{
		if(m_FirstMove)
		{
			return new BreakState(m_pBlockRef, m_pGridRef);
		}
		return new BlockIdleSate(m_pBlockRef, m_pGridRef);
	}

	return new MoveState(m_pBlockRef, m_pGridRef, m_Direction);
}