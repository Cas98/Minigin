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
	auto script = m_pBlockRef->GetComponent<BlockScript>();

	if(script)
	{
		script->SetIsPushed(false);
	}

	//check diamond alignment
	if(m_pBlockRef->GetTag() == "Diamond")
	{
		//auto script = m_pBlockRef->GetComponent<BlockScript>();
		if(script)
		{
			if(script->AreDiamondsAligned())
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
	/*auto script = m_pBlockRef->GetComponent<BlockScript>();

	if (script)
	{
		script->GetSubject()->RemoveObserver(this);
	}*/
}

void BlockIdleSate::Update()
{

}

dae::State* BlockIdleSate::HandleInput(dae::InputComponent* )
{
	auto script = m_pBlockRef->GetComponent<BlockScript>();
	if(script->GetIsPushed())
	{
		//pushed state
		return new PushedState(m_pBlockRef,m_pGridRef, m_pBlockRef->GetComponent<BlockScript>()->GetDirection(), true);
	}

	return nullptr;
}

