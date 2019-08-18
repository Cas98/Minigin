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
#include "SnobeeScript.h"
#include "GridScript.h"


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
	auto gridScript = m_pGridRef->GetComponent<GridScript>();
	glm::vec2 coords = gridComp->GetGameObjectPos(m_pPlayerRef);
	auto scriptComp = m_pPlayerRef->GetComponent<PlayerScript>();
	int height = gridComp->GetHeight();
	int width = gridComp->GetWidth();
	auto currentPlayerDir = scriptComp->GetDirection();

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
		//check if player activates wall
		if (coords.x == 0 && currentPlayerDir == dae::Direction::Left) gridScript->ActivateWall(dae::Direction::Left);
		if (coords.x == width - 1 && currentPlayerDir == dae::Direction::Right) gridScript->ActivateWall(dae::Direction::Right);
		if (coords.y == 0 && currentPlayerDir == dae::Direction::Down) gridScript->ActivateWall(dae::Direction::Down);
		if (coords.y == height - 1 && currentPlayerDir == dae::Direction::Up) gridScript->ActivateWall(dae::Direction::Up);

		return new PushState(m_pPlayerRef, m_pGridRef);
	}
	

	if(input->KeyboardDown('W'))
	{
		std::cout << "W pressed" << std::endl;
		scriptComp->SetDirection(dae::Direction::Up);

		if(coords.y < height - 1)
		{
			//bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x, coords.y + 1);
			/*if (obj)
			{
				if (obj->GetTag() == "Wall" || obj->GetTag() == "Diamond" || obj->GetTag() == "Snobee")
				{
					canMove = false;
				}
			}*/

			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Up, 96.0f);
			}
			else if(obj->GetTag() == "Snobee")
			{
				if(obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Up, 96.0f);
				}
			}
		}
	}

	if (input->KeyboardDown('A'))
	{
		std::cout << "A pressed" << std::endl;
		scriptComp->SetDirection(dae::Direction::Left);

		if (coords.x > 0)
		{
			//bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x - 1, coords.y);
			/*if (obj)
			{
				if (obj->GetTag() == "Wall" || obj->GetTag() == "Diamond")
				{
					canMove = false;
				}
			}*/

			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Left, 96.0f);
			}
			else if (obj->GetTag() == "Snobee")
			{
				if (obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Left, 96.0f);
				}
			}
		}
	}

	if (input->KeyboardDown('S'))
	{
		std::cout << "S pressed" << std::endl;
		scriptComp->SetDirection(dae::Direction::Down);
		
		if (coords.y > 0)
		{
			//bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x, coords.y - 1);
			/*if (obj)
			{
				if (obj->GetTag() == "Wall" || obj->GetTag() == "Diamond")
				{
					canMove = false;
				}
			}*/
			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Down, 96.0f);
			}
			else if (obj->GetTag() == "Snobee")
			{
				if (obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Down, 96.0f);
				}
			}
		}
	}

	if (input->KeyboardDown('D'))
	{
		std::cout << "D pressed" << std::endl;
		scriptComp->SetDirection(dae::Direction::Right);
		
		if (coords.x < width - 1)
		{
			//bool canMove = true;
			//check for wall
			auto obj = gridComp->GetGameObject(coords.x + 1, coords.y);
			/*if (obj)
			{
				if (obj->GetTag() == "Wall" || obj->GetTag() == "Diamond")
				{
					canMove = false;
				}
			}*/
			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Right, 96.0f);
			}
			else if (obj->GetTag() == "Snobee")
			{
				if (obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					return new MoveState(m_pPlayerRef, m_pGridRef, dae::Direction::Right, 96.0f);
				}
			}
		}
	}

	return nullptr;
}
