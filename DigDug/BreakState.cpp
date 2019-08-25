#include "pch.h"
#include "BreakState.h"
#include "GameObject.h"
#include "BlockScript.h"

BreakState::BreakState(dae::GameObject* pBlock)
	:m_pBlockRef(pBlock)
{
}

void BreakState::Enter()
{
	//delete block
	m_pBlockRef->GetComponent<BlockScript>()->Break();
}
