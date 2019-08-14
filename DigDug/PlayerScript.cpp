#include "pch.h"
#include "PlayerScript.h"
#include "GameObject.h"
#include "PlayerManagerScript.h"

PlayerScript::PlayerScript(dae::Direction direction, dae::GameObject* pPlayerManager)
	:m_Direction(direction), m_pPlayerManager(pPlayerManager)
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

dae::Direction PlayerScript::GetDirection() const
{
	return m_Direction;
}

void PlayerScript::SetDirection(dae::Direction direction)
{
	m_Direction = direction;
}

void PlayerScript::Kill()
{
	m_pPlayerManager->GetComponent<PlayerManagerScript>()->RespawnPlayer();
	GetGameObject()->Destroy();
}