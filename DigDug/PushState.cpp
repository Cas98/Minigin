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
	case Direction::Down:
		targetPos.y -= 1;
		break;
	case Direction::Up:
		targetPos.y += 1;
		break;
	case Direction::Right:
		targetPos.x += 1;
		break;
	case Direction::Left:
		targetPos.x -= 1;
		break;
	}


	//get target object
	auto targetObject = gridComp->GetGameObject(int(targetPos.x), int(targetPos.y));

	if(targetObject)
	{
		if(targetObject->GetTag() == "Wall" || targetObject->GetTag() == "Diamond")
		{
			targetObject->GetComponent<BlockScript>()->MoveBlock(direction);
		}
	}

	return new IdleState(m_pPlayerRef, m_pGridRef);
}