#include "pch.h"
#include "PlayerScript.h"


PlayerScript::PlayerScript(dae::Direction diretcion)
	:m_Direction(diretcion)
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