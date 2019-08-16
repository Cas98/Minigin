#include "pch.h"
#include "SnobeeIdleState.h"
#include "GameObject.h"
#include "SnobeeScript.h"
#include "GridComponent.h"
#include "MoveState.h"
#include "PlayerScript.h"
#include "PushedState.h"
#include "BlockScript.h"

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
	auto script = m_pSnobeeRef->GetComponent<SnobeeScript>();
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
	

	//select move direction
	auto snobeeScript = m_pSnobeeRef->GetComponent<SnobeeScript>();
	if (snobeeScript->GetIsPushed())
	{
		//pushed state
		return new PushedState(m_pSnobeeRef, m_pGridRef, m_pSnobeeRef->GetComponent<SnobeeScript>()->GetDirection(), false);
	}


	auto currentDirection = snobeeScript->GetDirection();
	//check if next spot is free
	auto gridComp = m_pGridRef->GetComponent<dae::GridComponent>();
	auto currentCoords = gridComp->GetGameObjectPos(m_pSnobeeRef);
	glm::vec2 nextCoords = currentCoords;
	int randDirChange = snobeeScript->GetRandomDirChange();

	switch (currentDirection)
	{
	case dae::Direction::Down:
		nextCoords.y -= 1;
		break;
	case dae::Direction::Up:
		nextCoords.y += 1;
		break;
	case dae::Direction::Left:
		nextCoords.x -= 1;
		break;
	case dae::Direction::Right:
		nextCoords.x += 1;
		break;
	}

	auto object = gridComp->GetGameObject(nextCoords.x, nextCoords.y);

	int height = gridComp->GetHeight();
	int width = gridComp->GetWidth();

	//if spot free move in that direction
	if (nextCoords.x >= 0 && nextCoords.x < width && nextCoords.y >= 0 && nextCoords.y < height && randDirChange > 0)
	{
		if (object == nullptr)
		{
			snobeeScript->DecrementRandomDirChange();
			return new MoveState(m_pSnobeeRef, m_pGridRef, currentDirection, 80.0f);
		}
		else if(object->GetTag() == "Player")
		{
			object->GetComponent<PlayerScript>()->Kill();
			snobeeScript->DecrementRandomDirChange();
			return new MoveState(m_pSnobeeRef, m_pGridRef, currentDirection, 80.0f);
		}
	}

	//Pick random new direction
	std::vector<dae::Direction> unavailableDirections;
	unavailableDirections.push_back(currentDirection);

	while(unavailableDirections.size() < 4)
	{
		auto randomDir = dae::Direction(rand() % 4);

		bool isNewDir = true;
		for (size_t i{0};  i < unavailableDirections.size(); ++i)
		{
			if (randomDir == unavailableDirections[i])
			{
				isNewDir = false;
				break;
			}
		}

		if(isNewDir)
		{
			unavailableDirections.push_back(randomDir);
			nextCoords = currentCoords;
			switch (randomDir)
			{
			case dae::Direction::Down:
				nextCoords.y -= 1;
				break;
			case dae::Direction::Up:
				nextCoords.y += 1;
				break;
			case dae::Direction::Left:
				nextCoords.x -= 1;
				break;
			case dae::Direction::Right:
				nextCoords.x += 1;
				break;
			}

			object = gridComp->GetGameObject(nextCoords.x, nextCoords.y);

			if (object == nullptr)
			{
				if (nextCoords.x >= 0 && nextCoords.x < width && nextCoords.y >= 0 && nextCoords.y < height)
				{
					snobeeScript->SetDirection(randomDir);
					snobeeScript->SetRandomDirChange();
					return new MoveState(m_pSnobeeRef, m_pGridRef, randomDir, 80.0f);
				}
			}
			/*else if(object->GetTag() == "Wall" || object->GetTag() == "Diamond")
			{
				if(object->GetComponent<BlockScript>()->GetIsPushed())return nullptr;
			}*/
		}
	}


	return nullptr;
}
