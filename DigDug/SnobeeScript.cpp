#include "pch.h"
#include "SnobeeScript.h"
#include "GameObject.h"

SnobeeScript::SnobeeScript(Direction direction, dae::GameObject* pSnobeeManger, bool isAi)
	:m_Direction(direction), m_pSnobeeManager(pSnobeeManger), m_IsAi(isAi)
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

Direction SnobeeScript::GetDirection() const
{
	return m_Direction;
}

void SnobeeScript::SetDirection(Direction direction)
{
	m_Direction = direction;
}

void SnobeeScript::SetRandomDirChange()
{
	srand(m_Direction * m_RandomDirChange);
	m_RandomDirChange = rand() % 3 + 6;
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
	if (!m_IsAi)script->SetIsNextSnobeePlayer(true);
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

void  SnobeeScript::OnNotify(dae::GameObject* , const std::string& message)
{
	if(message == "Stun")
	{
		SetIsStunned(true);
	}
}

bool SnobeeScript::GetIsAi()const
{
	return m_IsAi;
}