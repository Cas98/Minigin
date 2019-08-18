#include "pch.h"
#include "SnobeeScript.h"
#include "GameObject.h"

SnobeeScript::SnobeeScript(dae::Direction direction, dae::GameObject* pSnobeeManger)
	:m_Direction(direction), m_pSnobeeManager(pSnobeeManger)
{

}


SnobeeScript::~SnobeeScript()
{
}

void SnobeeScript::Init()
{
	SetRandomDirChange();
}

void SnobeeScript::Update()
{

}

dae::Direction SnobeeScript::GetDirection() const
{
	return m_Direction;
}

void SnobeeScript::SetDirection(dae::Direction direction)
{
	m_Direction = direction;
}

void SnobeeScript::SetRandomDirChange()
{
	m_RandomDirChange = rand() % 3 + 7;
}

void SnobeeScript::DecrementRandomDirChange()
{
	--m_RandomDirChange;
}

int SnobeeScript::GetRandomDirChange() const
{
	return m_RandomDirChange;
}

void SnobeeScript::Kill()
{
	auto script = m_pSnobeeManager->GetComponent<SnobeeManagerScript>();
	script->DecrementActiveSnobees();
	script->RemoveObserver(this);
	GetGameObject()->Destroy();
}

void SnobeeScript::SetIsPushed(bool isPushed)
{
	m_IsPushed = isPushed;
	std::cout << "IS PUSHED !!!!!!!!!!!!!!!!!!!!" << std::endl;
}

bool SnobeeScript::GetIsPushed() const
{
	return m_IsPushed;
}

void SnobeeScript::SetIsStunned(bool isStunned)
{
	m_IsStunned = isStunned;
}

bool SnobeeScript::GetIsStunned() const
{
	return m_IsStunned;
}

void SnobeeScript::Stun()
{
	SetIsStunned(true);
}

void  SnobeeScript::OnNotify(dae::GameObject* gameObject, const std::string& message)
{
	if(message == "Stun")
	{
		SetIsStunned(true);
	}
}