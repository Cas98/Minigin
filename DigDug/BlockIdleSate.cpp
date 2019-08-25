#include "pch.h"
#include "BlockIdleSate.h"
#include "GameObject.h"
#include "BlockScript.h"
#include "PushedState.h"
#include "SubjectComponent.h"

BlockIdleSate::BlockIdleSate(dae::GameObject* pBlock, dae::GameObject* pGrid)
	:m_pBlockRef(pBlock), m_pGridRef(pGrid)
{
}

void BlockIdleSate::Enter()
{
	m_pBlockScriptRef = m_pBlockRef->GetComponent<BlockScript>();

	if(m_pBlockScriptRef)
	{
		m_pBlockScriptRef->SetIsPushed(false);
	}

	//check diamond alignment
	if(m_pBlockRef->GetTag() == "Diamond")
	{
		if(m_pBlockScriptRef)
		{
			if(m_pBlockScriptRef->AreDiamondsAligned())
			{
				std::cout << "Diamonds are aligned!!!" << std::endl;
				m_pBlockRef->GetComponent<dae::SubjectComponent>()->Notify(m_pBlockRef, "DiamondsAligned");//add score for aligning diamonds
			}
			else
			{
				std::cout << "Diamonds are NOT aligned" << std::endl;
			}
		}
	}
}

void BlockIdleSate::Exit()
{

}

void BlockIdleSate::Update()
{

}

dae::State* BlockIdleSate::HandleInput(dae::InputComponent* )
{
	if(m_pBlockScriptRef->GetIsPushed())
	{
		//pushed state
		return new PushedState(m_pBlockRef,m_pGridRef, m_pBlockScriptRef->GetDirection(), true);
	}

	return nullptr;
}

