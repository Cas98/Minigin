#include "pch.h"
#include "PlayerScript.h"
#include "GameObject.h"
#include "PlayerManagerScript.h"
#include "InputComponent.h"

PlayerScript::PlayerScript(Direction direction, dae::GameObject* pPlayerManager, glm::vec2 spawnCoords)
	:m_Direction(direction), m_pPlayerManager(pPlayerManager), m_SpawnCoords(spawnCoords)
{

}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::Init()
{
	
}

void PlayerScript::Update()
{
	
}

Direction PlayerScript::GetDirection() const
{
	return m_Direction;
}

void PlayerScript::SetDirection(Direction direction)
{
	m_Direction = direction;
	switch(direction)
	{
	case Direction::Down:
			GetGameObject()->GetTransformComponent()->SetRotation(0);
			break;
	case Direction::Up:
		GetGameObject()->GetTransformComponent()->SetRotation(180);
		break;
	case Direction::Left:
		GetGameObject()->GetTransformComponent()->SetRotation(90);
		break;
	case Direction::Right:
		GetGameObject()->GetTransformComponent()->SetRotation(270);
		break;
	}
}

void PlayerScript::Kill()
{
	int playerIndex = GetGameObject()->GetComponent<dae::InputComponent>()->GetPlayerIndex();
	m_pPlayerManager->GetComponent<PlayerManagerScript>()->RespawnPlayer(int(m_SpawnCoords.x), int(m_SpawnCoords.y),playerIndex);
	GetGameObject()->Destroy();
}

glm::vec2 PlayerScript::GetSpawnCoords() const
{
	return m_SpawnCoords;
}