#include "pch.h"
#include "SnobeeIdleState.h"
#include "GameObject.h"
#include "SnobeeScript.h"
#include "GridComponent.h"
#include "MoveState.h"
#include "PlayerScript.h"
#include "PushedState.h"
#include "BlockScript.h"
#include "StunState.h"
#include "GridScript.h"

SnobeeIdleState::SnobeeIdleState(dae::GameObject* pSnobee, dae::GameObject* pGrid)
	:m_pSnobeeRef(pSnobee), m_pGridRef(pGrid)
{
}


SnobeeIdleState::~SnobeeIdleState()
{
}

void SnobeeIdleState::Enter()
{
	//std::cout << "Enter snobee idle state" << std::endl;
	/*auto script = m_pSnobeeRef->GetComponent<SnobeeScript>();*/
}

void SnobeeIdleState::Exit()
{
	//std::cout << "Exit snobee idle state" << std::endl;
}

void SnobeeIdleState::Update()
{

}

dae::State* SnobeeIdleState::HandleInput(dae::InputComponent* input)
{
	auto snobeeScript = m_pSnobeeRef->GetComponent<SnobeeScript>();
	auto gridScript = m_pGridRef->GetComponent<GridScript>();
	auto gridComp = m_pGridRef->GetComponent<dae::GridComponent>();
	auto currentCoords = gridComp->GetGameObjectPos(m_pSnobeeRef);
	int height = gridComp->GetHeight();
	int width = gridComp->GetWidth();

	//check if stunned by active wall
	if (currentCoords.x == 0 && gridScript->IsWallActive(Direction::Left)) return new StunState(m_pSnobeeRef, m_pGridRef, 5.0f);
	if (currentCoords.x == width - 1 && gridScript->IsWallActive(Direction::Right)) return new StunState(m_pSnobeeRef, m_pGridRef, 5.0f);
	if (currentCoords.y == 0 && gridScript->IsWallActive(Direction::Down)) return new StunState(m_pSnobeeRef, m_pGridRef, 5.0f);
	if (currentCoords.y == height - 1 && gridScript->IsWallActive(Direction::Up)) return new StunState(m_pSnobeeRef, m_pGridRef, 5.0f);

	if (snobeeScript->GetIsPushed())
	{
		//pushed state
		return new PushedState(m_pSnobeeRef, m_pGridRef, m_pSnobeeRef->GetComponent<SnobeeScript>()->GetDirection(), false);
	}
	if (snobeeScript->GetIsStunned())
	{
		//stun state
		return new StunState(m_pSnobeeRef, m_pGridRef, 5.0f);
	}


	if(m_pSnobeeRef->GetComponent<SnobeeScript>()->GetIsAi())
	{
		return HandleAi();
	}
	else
	{
		return HandlePlayer(input);
	}
}


dae::State* SnobeeIdleState::HandleAi()
{

	auto snobeeScript = m_pSnobeeRef->GetComponent<SnobeeScript>();
	auto currentDirection = snobeeScript->GetDirection();
	auto gridComp = m_pGridRef->GetComponent<dae::GridComponent>();
	auto currentCoords = gridComp->GetGameObjectPos(m_pSnobeeRef);
	glm::vec2 nextCoords = currentCoords;
	//select move direction
	int randDirChange = snobeeScript->GetRandomDirChange();
	int height = gridComp->GetHeight();
	int width = gridComp->GetWidth();

	//check if next spot is free
	switch (currentDirection)
	{
	case Direction::Down:
		nextCoords.y -= 1;
		break;
	case Direction::Up:
		nextCoords.y += 1;
		break;
	case Direction::Left:
		nextCoords.x -= 1;
		break;
	case Direction::Right:
		nextCoords.x += 1;
		break;
	}

	auto object = gridComp->GetGameObject(int(nextCoords.x), int(nextCoords.y));
	
	//if spot free move in that direction
	if (nextCoords.x >= 0 && nextCoords.x < width && nextCoords.y >= 0 && nextCoords.y < height && randDirChange > 0)
	{
		if (object == nullptr)
		{
			snobeeScript->DecrementRandomDirChange();
			return new MoveState(m_pSnobeeRef, m_pGridRef, currentDirection, 80.0f);
		}
		else if (object)
		{
			if (object->GetTag() == "Player")//if player kill
			{
				object->GetComponent<PlayerScript>()->Kill();
				snobeeScript->DecrementRandomDirChange();
				return new MoveState(m_pSnobeeRef, m_pGridRef, currentDirection, 80.0f);
			}
		}
	}

	//Pick random new direction
	std::vector<Direction> availableDirections{Direction::Down,Direction::Up,Direction::Left,Direction::Right };
	auto it = std::find(availableDirections.begin(), availableDirections.end(), currentDirection);
	availableDirections.erase(it);
	int number = rand() % 10000000;
	while (availableDirections.size() > 0)
	{
		srand(number);
		auto randomDir = availableDirections[((rand() % 100000) % availableDirections.size())];
		auto itDir = std::find(availableDirections.begin(), availableDirections.end(), randomDir);
		availableDirections.erase(itDir);
			
		nextCoords = currentCoords;
		switch (randomDir)
		{
		case Direction::Down:
			nextCoords.y -= 1;
			break;
		case Direction::Up:
			nextCoords.y += 1;
			break;
		case Direction::Left:
			nextCoords.x -= 1;
			break;
		case Direction::Right:
			nextCoords.x += 1;
			break;
		}

		object = gridComp->GetGameObject(int(nextCoords.x), int(nextCoords.y));

		if (object == nullptr)
		{
			if (nextCoords.x >= 0 && nextCoords.x < width && nextCoords.y >= 0 && nextCoords.y < height)
			{
				snobeeScript->SetDirection(randomDir);
				if (randomDir <= 4)snobeeScript->SetRandomDirChange();
				return new MoveState(m_pSnobeeRef, m_pGridRef, randomDir, 80.0f);
			}
		}
		else if(object->GetTag() == "Player")//if player kill
		{
			object->GetComponent<PlayerScript>()->Kill();
			if(randomDir <= 4)snobeeScript->SetRandomDirChange();
			snobeeScript->SetDirection(randomDir);
			return new MoveState(m_pSnobeeRef, m_pGridRef, randomDir, 80.0f);
		}
					
		number += rand() % 10000000000;
	}

	return nullptr;
}

dae::State* SnobeeIdleState::HandlePlayer(dae::InputComponent* input)
{
	auto gridComp = m_pGridRef->GetComponent<dae::GridComponent>();
	glm::vec2 coords = gridComp->GetGameObjectPos(m_pSnobeeRef);
	auto scriptComp = m_pSnobeeRef->GetComponent<SnobeeScript>();
	int height = gridComp->GetHeight();
	int width = gridComp->GetWidth();

	//set key inputs
	char moveUp = 38;
	char moveDown = 40;
	char moveRight = 39;
	char moveLeft = 37;
	
	if (input->KeyboardDown(moveUp) || input->GamepadDown(dae::ControllerButton::DpadUp))
	{
		scriptComp->SetDirection(Direction::Up);

		if (coords.y < height - 1)
		{
			//check for wall
			auto obj = gridComp->GetGameObject(int(coords.x), int(coords.y + 1));

			if (obj == nullptr)
			{
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Up, 80.0f);
			}
			else if (obj->GetTag() == "Player")//if player kill
			{
				obj->GetComponent<PlayerScript>()->Kill();
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Up, 80.0f);
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
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Left, 80.0f);
			}
			else if (obj->GetTag() == "Player")//if player kill
			{
				obj->GetComponent<PlayerScript>()->Kill();
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Left, 80.0f);
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
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Down, 80.0f);
			}
			else if (obj->GetTag() == "Player")//if player kill
			{
				obj->GetComponent<PlayerScript>()->Kill();
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Down, 80.0f);
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
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Right, 80.0f);
			}
			else if (obj->GetTag() == "Player")//if player kill
			{
				obj->GetComponent<PlayerScript>()->Kill();
				return new MoveState(m_pSnobeeRef, m_pGridRef, Direction::Right, 80.0f);
			}
		}
	}
	return nullptr;
}