#include "pch.h"
#include "PushedState.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "BlockIdleSate.h"
#include "MoveState.h"
#include "BreakState.h"
#include "SnobeeScript.h"
#include "BlockScript.h"
#include "PlayerScript.h"

PushedState::PushedState(dae::GameObject* pBlock, dae::GameObject* pGrid, dae::Direction direction, bool firstMove)
	:m_pBlockRef(pBlock), m_pGridRef(pGrid), m_Direction(direction), m_FirstMove(firstMove)
{
}


PushedState::~PushedState()
{
}


dae::State* PushedState::HandleInput(dae::InputComponent* )
{
	//get target position

	auto gridcomp = m_pGridRef->GetComponent<dae::GridComponent>();
	glm::vec2 coords = gridcomp->GetGameObjectPos(m_pBlockRef);

	switch(m_Direction)
	{
	case dae::Direction::Down:
		coords.y -= 1;
		break;
	case dae::Direction::Up:
		coords.y += 1;
		break;
	case dae::Direction::Left:
		coords.x -= 1;
		break;
	case dae::Direction::Right:
		coords.x += 1;
		break;
	}

	int height = gridcomp->GetHeight();
	int width = gridcomp->GetWidth();

	auto targetObj = gridcomp->GetGameObject(int(coords.x), int(coords.y));

	//check if can move
	bool isBlocked = false;

	if(targetObj)
	{
		if(targetObj->GetTag() == "Wall" || targetObj->GetTag() == "Diamond" || targetObj->GetTag() == "Player")//blocks only
		{
			isBlocked = true;
		}
		else if(targetObj->GetTag() == "Snobee")//if next block is a snobee
		{
			if(m_pBlockRef->GetTag() == "Snobee")//if pushed block is also snobee kill it
			{
				isBlocked = true;
			}
			else//if pushed block is not a snobee push it
			{
				targetObj->GetComponent<SnobeeScript>()->SetDirection(m_Direction);
				targetObj->GetComponent<SnobeeScript>()->SetIsPushed(true);
				return nullptr;
			}
		}
		if (targetObj->GetTag() == "Player" && m_pBlockRef->GetTag() == "Snobee")
		{
			gridcomp->RemoveGameObject(targetObj);
			targetObj->GetComponent<PlayerScript>()->Kill();
			isBlocked = false;
		}
	}


	//if cant move go back to idle / if just pushed break
	if(coords.x < 0 || coords.x >= width || coords.y < 0 || coords.y >= height || isBlocked)
	{
		if (m_pBlockRef->GetTag() != "Snobee")
		{
			if (m_FirstMove && m_pBlockRef->GetTag() != "Diamond")
			{
				return new BreakState(m_pBlockRef, m_pGridRef);
			}
			return new BlockIdleSate(m_pBlockRef, m_pGridRef);
		}
		else//if snobee cant move anymore kill it
		{
			gridcomp->RemoveGameObject(m_pBlockRef);
			m_pBlockRef->GetComponent<SnobeeScript>()->Kill();
		}
	}

	//move
	return new MoveState(m_pBlockRef, m_pGridRef, m_Direction);
}