#include "pch.h"
#include "PushState.h"
#include "GameObject.h"
#include "PlayerScript.h"
#include "GridComponent.h"
#include "BlockScript.h"
#include "IdleState.h"

PushState::PushState(dae::GameObject* pPlayer, dae::GameObject* pGrid)
	:m_pPlayerRef(pPlayer), m_pGridRef(pGrid)
{
}


PushState::~PushState()
{
}

dae::State* PushState::HandleInput(dae::InputComponent* )
{
	//get player direction
	auto direction = m_pPlayerRef->GetComponent<PlayerScript>()->GetDirection();

	//get push target
	auto gridComp = m_pGridRef->GetComponent<dae::GridComponent>();
	auto targetPos = gridComp->GetGameObjectPos(m_pPlayerRef);

	switch(direction)
	{
	case dae::Direction::Down:
		targetPos.y -= 1;
		break;
	case dae::Direction::Up:
		targetPos.y += 1;
		break;
	case dae::Direction::Right:
		targetPos.x += 1;
		break;
	case dae::Direction::Left:
		targetPos.x -= 1;
		break;
	}


	//get target object
	auto targetObject = gridComp->GetGameObject(targetPos.x, targetPos.y);

	if(targetObject)
	{
		if(targetObject->GetTag() == "Wall")
		{
			targetObject->GetComponent<BlockScript>()->MoveBlock(direction);
		}
	}

	return new IdleState(m_pPlayerRef, m_pGridRef);
}