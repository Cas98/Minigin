#include "pch.h"
#include "BlockIdleSate.h"
#include "GameObject.h"
#include "ScriptComponent.h"
#include "BlockScript.h"
#include "PushedState.h"

BlockIdleSate::BlockIdleSate(dae::GameObject* pBlock, dae::GameObject* pGrid)
	:m_pBlockRef(pBlock), m_pGridRef(pGrid)
{
}

void BlockIdleSate::Enter()
{
	auto script = m_pBlockRef->GetComponent<BlockScript>();

	if(script)
	{
		script->GetSubject()->AddObserver(this);
	}
}

void BlockIdleSate::Exit()
{
	auto script = m_pBlockRef->GetComponent<BlockScript>();

	if (script)
	{
		script->GetSubject()->RemoveObserver(this);
	}
}

void BlockIdleSate::Update()
{
	
}

dae::State* BlockIdleSate::HandleInput(dae::InputComponent* )
{
	if(m_Move)
	{
		//pushed state
		return new PushedState(m_pBlockRef,m_pGridRef, m_pBlockRef->GetComponent<BlockScript>()->GetDirection(), true);
	}

	return nullptr;
}

void BlockIdleSate::OnNotify(std::string message)
{
	if(message == "Move")
	{
		m_Move = true;
	}
}
