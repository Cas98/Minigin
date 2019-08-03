#include "pch.h"
#include "BreakState.h"
#include "GameObject.h"
#include "GridComponent.h"

BreakState::BreakState(dae::GameObject* pBlock, dae::GameObject* pGrid)
	:m_pBlockRef(pBlock), m_pGridRef(pGrid)
{
}

void BreakState::Enter()
{
	//remove block from grid
	m_pGridRef->GetComponent<dae::GridComponent>()->RemoveGameObject(m_pBlockRef);

	//delete block
	m_pBlockRef->Destroy();
}
