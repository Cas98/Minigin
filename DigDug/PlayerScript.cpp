#include "pch.h"
#include "PlayerScript.h"
#include "GameObject.h"

PlayerScript::PlayerScript(dae::Direction direction)
	:m_Direction(direction)
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
	GetGameObject()->Destroy();
}