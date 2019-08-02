#include "pch.h"
#include "IdleState.h"
#include "MoveState.h"
#include "GameObject.h"
#include "GridComponent.h"


IdleState::IdleState(dae::GameObject* pPlayer, dae::GameObject* pGrid)
	:m_pPlayerRef(pPlayer), m_pGridRef(pGrid)
{
}


IdleState::~IdleState()
{
}

void IdleState::Enter()
{
	std::cout << "Enter idle state" << std::endl;
}

void IdleState::Exit()
{
	std::cout << "Exit idle state" << std::endl;
}

void IdleState::Update()
{
	
}

dae::State* IdleState::HandleInput(dae::InputComponent* input)
{
	if(input->KeyboardDown('W'))
	{
		std::cout << "W pressed" << std::endl;

		auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
		glm::vec2 coords = gridcomp->GetGameObjectPos(m_pPlayerRef);
		int height = gridcomp->GetHeight();

		if(coords.y < height - 1)
		{
			return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Up);
		}

		return nullptr;
	}

	if (input->KeyboardDown('A'))
	{

		std::cout << "A pressed" << std::endl;

		auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
		glm::vec2 coords = gridcomp->GetGameObjectPos(m_pPlayerRef);

		if (coords.x > 0)
		{
			return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Left);
		}

		return nullptr;
	}

	if (input->KeyboardDown('S'))
	{
		std::cout << "S pressed" << std::endl;

		auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
		glm::vec2 coords = gridcomp->GetGameObjectPos(m_pPlayerRef);

		if (coords.y > 0)
		{
			return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Down);
		}

		return nullptr;
	}

	if (input->KeyboardDown('D'))
	{
		std::cout << "D pressed" << std::endl;

		auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
		glm::vec2 coords = gridcomp->GetGameObjectPos(m_pPlayerRef);
		int width = gridcomp->GetWidth();

		if (coords.x < width - 1)
		{
			return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Right);
		}

		return nullptr;
	}

	return nullptr;
}
