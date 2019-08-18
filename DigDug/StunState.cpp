#include "pch.h"
#include "StunState.h"
#include "GameObject.h"
#include "SnobeeScript.h"
#include "Time.h"
#include "SnobeeIdleState.h"
#include "PushedState.h"

StunState::StunState(dae::GameObject* pSnobee, dae::GameObject* pGrid, float stunTime)
	:m_pSnobeeRef(pSnobee), m_pGridRef(pGrid), m_StunTime(stunTime)
{
}

StunState::~StunState()
{
}

void StunState::Enter()
{
	m_pSnobeeRef->GetComponent<SnobeeScript>()->SetIsStunned(true);
}

void StunState::Exit()
{
	m_pSnobeeRef->GetComponent<SnobeeScript>()->SetIsStunned(false);
}

void StunState::Update()
{
	
}

dae::State* StunState::HandleInput(dae::InputComponent* input)
{
	m_StunTime -= dae::Time::GetInstance().GetDeltaTime();
	if(m_StunTime <= 0.0f)
	{
		return new SnobeeIdleState(m_pSnobeeRef, m_pGridRef);
	}
	auto snobeeScript = m_pSnobeeRef->GetComponent<SnobeeScript>();
	if (snobeeScript->GetIsPushed())
	{
		//pushed state
		return new PushedState(m_pSnobeeRef, m_pGridRef, m_pSnobeeRef->GetComponent<SnobeeScript>()->GetDirection(), false);
	}

	return nullptr;
}