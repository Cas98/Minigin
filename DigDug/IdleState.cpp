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
#include "SubjectComponent.h"


IdleState::IdleState(dae::GameObject* pPlayer, dae::GameObject* pGrid)
	:m_pPlayerRef(pPlayer), m_pGridRef(pGrid)
{
}


IdleState::~IdleState()
{
}

void IdleState::Enter()
{
}

void IdleState::Exit()
{
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


	//set key inputs
	char pushKey = 'Q';
	char moveUp = 'W';
	char moveDown = 'S';
	char moveRight = 'D';
	char moveLeft = 'A';
	int playerIndex = input->GetPlayerIndex();
	if(playerIndex == 1)
	{
		pushKey = 13;
		moveUp = 38;
		moveDown = 40;
		moveRight = 39;
		moveLeft = 37;
	}

	//enter push state
	if (input->KeyboardPressed(pushKey) || input->GamepadDown(dae::ControllerButton::ButtonA))
	{
		//check if player activates wall
		if (coords.x == 0 && currentPlayerDir == Direction::Left) gridScript->ActivateWall(Direction::Left);
		if (coords.x == width - 1 && currentPlayerDir == Direction::Right) gridScript->ActivateWall(Direction::Right);
		if (coords.y == 0 && currentPlayerDir == Direction::Down) gridScript->ActivateWall(Direction::Down);
		if (coords.y == height - 1 && currentPlayerDir == Direction::Up) gridScript->ActivateWall(Direction::Up);

		return new PushState(m_pPlayerRef, m_pGridRef);
	}
	

	if(input->KeyboardDown(moveUp) || input->GamepadDown(dae::ControllerButton::DpadUp))
	{
		//std::cout << "W pressed" << std::endl;
		scriptComp->SetDirection(Direction::Up);

		if(coords.y < height - 1)
		{
			//check for wall
			auto obj = gridComp->GetGameObject(int(coords.x), int (coords.y + 1));

			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Up, 96.0f);
			}
			else if(obj->GetTag() == "Snobee")
			{
				if(obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					m_pPlayerRef->GetComponent<dae::SubjectComponent>()->Notify(m_pPlayerRef, "KillStunnedSnobee");//add score for killing stunned snobee
					return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Up, 96.0f);
				}
				else
				{
					gridComp->RemoveGameObject(m_pPlayerRef);
					scriptComp->Kill();
				}
			}
		}
	}

	if (input->KeyboardDown(moveLeft) || input->GamepadDown(dae::ControllerButton::DpadLeft))
	{
		scriptComp->SetDirection(Direction::Left);

		if (coords.x > 0)
		{
			//check for wall
			auto obj = gridComp->GetGameObject(int(coords.x - 1), int(coords.y));

			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Left, 96.0f);
			}
			else if (obj->GetTag() == "Snobee")
			{
				if (obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					m_pPlayerRef->GetComponent<dae::SubjectComponent>()->Notify(m_pPlayerRef, "KillStunnedSnobee");//add score for killing stunned snobee
					return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Left, 96.0f);
				}
				else
				{
					gridComp->RemoveGameObject(m_pPlayerRef);
					scriptComp->Kill();
				}
			}
		}
	}

	if (input->KeyboardDown(moveDown) || input->GamepadDown(dae::ControllerButton::DpadDown))
	{
		scriptComp->SetDirection(Direction::Down);
		
		if (coords.y > 0)
		{
			//check for wall
			auto obj = gridComp->GetGameObject(int(coords.x), int(coords.y - 1));
	
			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Down, 96.0f);
			}
			else if (obj->GetTag() == "Snobee")
			{
				if (obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					m_pPlayerRef->GetComponent<dae::SubjectComponent>()->Notify(m_pPlayerRef, "KillStunnedSnobee");//add score for killing stunned snobee
					return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Down, 96.0f);
				}
				else
				{
					gridComp->RemoveGameObject(m_pPlayerRef);
					scriptComp->Kill();
				}
			}
		}
	}

	if (input->KeyboardDown(moveRight) || input->GamepadDown(dae::ControllerButton::DpadRight))
	{
		scriptComp->SetDirection(Direction::Right);
		
		if (coords.x < width - 1)
		{
			//check for wall
			auto obj = gridComp->GetGameObject(int(coords.x + 1), int(coords.y));
			
			if (obj == nullptr)
			{
				return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Right, 96.0f);
			}
			else if (obj->GetTag() == "Snobee")
			{
				if (obj->GetComponent<SnobeeScript>()->GetIsStunned())
				{
					obj->GetComponent<SnobeeScript>()->Kill();
					m_pPlayerRef->GetComponent<dae::SubjectComponent>()->Notify(m_pPlayerRef, "KillStunnedSnobee");//add score for killing stunned snobee
					return new MoveState(m_pPlayerRef, m_pGridRef, Direction::Right, 96.0f);
				}
				else
				{
					gridComp->RemoveGameObject(m_pPlayerRef);
					scriptComp->Kill();
				}
			}
		}
	}

	
	return nullptr;
}


