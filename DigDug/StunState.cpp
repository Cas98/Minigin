#include "pch.h"
#include "StunState.h"
#include "GameObject.h"
#include "SnobeeScript.h"
#include "Time.h"
#include "SnobeeIdleState.h"
#include "PushedState.h"
#include "TextureComponent.h"

StunState::StunState(dae::GameObject* pSnobee, dae::GameObject* pGrid, float stunTime)
	:m_pSnobeeRef(pSnobee), m_pGridRef(pGrid), m_StunTime(stunTime)
{
}

StunState::~StunState()
{
}

void StunState::Enter()
{
	auto script = m_pSnobeeRef->GetComponent<SnobeeScript>();
	script->SetIsStunned(true);

	std::string path{ "Images/SnobeeStunned.png" };
	if (!script->GetIsAi()) path = "Images/SnobeeYellowStunned.png";
	m_pSnobeeRef->GetComponent<dae::TextureComponent>()->SetTexture(path);
}

void StunState::Exit()
{
	auto script = m_pSnobeeRef->GetComponent<SnobeeScript>();
	script->SetIsStunned(false);

	std::string path{ "Images/Snobee.png" };
	if (!script->GetIsAi()) path = "Images/SnobeeYellow.png";
	m_pSnobeeRef->GetComponent<dae::TextureComponent>()->SetTexture(path);
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