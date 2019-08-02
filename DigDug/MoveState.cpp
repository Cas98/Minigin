#include "pch.h"
#include "MoveState.h"
#include "IdleState.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "Time.h"


MoveState::MoveState(dae::GameObject* pPlayer, dae::GameObject* pGrid, dae::Direction dir)
	:m_pPlayerRef(pPlayer), m_pGridRef(pGrid)
{
	switch(dir)
	{
	case dae::Direction::Down:
		m_Direction = { 0,-1 };
		break;
	case dae::Direction::Up:
		m_Direction = { 0,1 };
		break;
	case dae::Direction::Right:
		m_Direction = { 1,0 };
		break;
	case dae::Direction::Left:
		m_Direction = { -1,0 };
		break;
	}
}


MoveState::~MoveState()
{
}


void MoveState::Enter()
{
	std::cout << "Enter move state" << std::endl;


	//get offset from grid component
	m_Offset = m_pGridRef->GetComponent<dae::GridComponent>()->GetOffset();
}

void MoveState::Exit()
{
	std::cout << "Exit move state" << std::endl;

	//set object on new position on the grid
	auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
	glm::vec2 coords = gridcomp->GetGameObjectPos(m_pPlayerRef);
	gridcomp->RemoveGameObject(int(coords.x), int(coords.y));
	coords += m_Direction;
	gridcomp->SetGameObject(coords.x, coords.y, m_pPlayerRef);
	std::cout << "Player coords: " << coords.x << ", " << coords.y << std::endl;
}

void MoveState::Update()
{
	//move 
	glm::vec2 translation = m_Direction * dae::Time::GetInstance().GetDeltaTime() * m_Speed;
	m_pPlayerRef->GetTransformComponent()->Translate(translation.x, translation.y);

	m_Offset -= abs(translation.x);
	m_Offset -= abs(translation.y);

	if(m_Offset <= 0.0f)
	{
		m_ChangeState = true;
	}
}

dae::State* MoveState::HandleInput(dae::InputComponent* )
{
	if(m_ChangeState)
	{
		return new IdleState(m_pPlayerRef, m_pGridRef);
	}

	return nullptr;
}