#include "pch.h"
#include "IdleState.h"
#include "MoveState.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "ScriptComponent.h"
#include "BlockScript.h"
#include "TextureComponent.h"
#include "PlayerScript.h"
#include "PushState.h"


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

	auto gridComp = m_pGridRef->GetComponent<dae::GridComponent>();
	glm::vec2 coords = gridComp->GetGameObjectPos(m_pPlayerRef);
	auto scriptComp = m_pPlayerRef->GetComponent<PlayerScript>();

	//enter push state
	if (input->KeyboardPressed('Z'))
	{
		/*auto obj = gridComp->GetGameObject(coords.x + 1, coords.y );
		if (obj)
		{
			if (obj->GetTag() == "Wall")
			{
				auto script = obj->GetComponent<BlockScript>();
				if (script)
				{
					script->MoveBlock(dae::Direction::Right);	
				}
			}
		}*/
		return new PushState(m_pPlayerRef, m_pGridRef);
	}
	

	if(input->KeyboardDown('W'))
	{
		std::cout << "W pressed" << std::endl;
		int height = gridComp->GetHeight();

		scriptComp->SetDirection(dae::Direction::Up);

		if(coords.y < height - 1)
		{
			bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x, coords.y + 1);
			if (obj)
			{
				if (obj->GetTag() == "Wall")
				{
					canMove = false;
				}
			}

			if (canMove)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Up);
			}
		}
	}

	if (input->KeyboardDown('A'))
	{
		std::cout << "A pressed" << std::endl;

		scriptComp->SetDirection(dae::Direction::Left);

		if (coords.x > 0)
		{
			bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x - 1, coords.y);
			if (obj)
			{
				if (obj->GetTag() == "Wall")
				{
					canMove = false;
				}
			}

			if (canMove)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Left);
			}
		}
	}

	if (input->KeyboardDown('S'))
	{
		std::cout << "S pressed" << std::endl;

		scriptComp->SetDirection(dae::Direction::Down);
		
		if (coords.y > 0)
		{
			bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x, coords.y - 1);
			if (obj)
			{
				if (obj->GetTag() == "Wall")
				{
					canMove = false;
				}
			}
			if (canMove)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Down);
			}
		}
	}

	if (input->KeyboardDown('D'))
	{
		std::cout << "D pressed" << std::endl;
		int width = gridComp->GetWidth();

		scriptComp->SetDirection(dae::Direction::Right);
		
		if (coords.x < width - 1)
		{
			bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x + 1, coords.y);
			if (obj)
			{
				if (obj->GetTag() == "Wall")
				{
					canMove = false;
				}
			}
			if (canMove)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Right);
			}
		}
	}

	return nullptr;
}
