#include "pch.h"
#include "BlockScript.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "SnobeeManagerScript.h"

BlockScript::BlockScript(dae::GameObject* pGrid, dae::GameObject* pSnobeeManger, bool canSpawnSnobee)
	:m_CanSpawnSnobee(canSpawnSnobee), m_pSnobeeManager(pSnobeeManger)
{
	//m_pSubject = new Subject();
	m_pGridCompRef = pGrid->GetComponent<dae::GridComponent>();
}

BlockScript::~BlockScript()
{
	//delete m_pSubject;
}

void BlockScript::Init()
{
}

void BlockScript::Update()
{
	
}

void BlockScript::MoveBlock(const dae::Direction& newDirection)
{
	m_Direction = newDirection;
	//m_pSubject->Notify("Move");
	SetIsPushed(true);
}

//Subject* BlockScript::GetSubject() const
//{
//	return m_pSubject;
//}

dae::Direction BlockScript::GetDirection() const
{
	return m_Direction;
}

bool BlockScript::AreDiamondsAligned()
{
	//auto gridComp = pGrid->GetComponent<dae::GridComponent>();
	auto gridCoords = m_pGridCompRef->GetGameObjectPos(GetGameObject());
	std::vector<glm::vec2> directions = { {1,0},{0,1},{-1,0},{0,-1} };


	for(size_t i{0}; i < directions.size(); ++i)
	{
		auto targetPos = gridCoords + directions[i];
		
		if(IsObjectDiamond(targetPos))
		{
			//option 1
			targetPos = gridCoords + (2.0f * directions[i]);
			
			if(IsObjectDiamond(targetPos))
			{
				return true;
			}

			//option 2 
			targetPos = gridCoords - directions[i];

			if(IsObjectDiamond(targetPos))
			{
				return true;
			}

			return false;
		}
	}

	return false;
}

bool BlockScript::IsObjectDiamond(glm::vec2 targetPos)
{
	auto neighbouringObject = m_pGridCompRef->GetGameObject(int(targetPos.x), int(targetPos.y));

	if (neighbouringObject)
	{
		if (neighbouringObject->GetTag() == "Diamond")
		{
			return true;
		}
	}

	return false;
}

void BlockScript::SetIsPushed(bool isPushed)
{
	m_IsPushed = isPushed;
}

bool BlockScript::GetIsPushed() const
{
	return m_IsPushed;
}

void BlockScript::Break()
{
	//remove block from grid
	m_pGridCompRef->RemoveGameObject(GetGameObject());

	//destroy gameobject
	GetGameObject()->Destroy();

	if(m_CanSpawnSnobee && m_pSnobeeManager)
	{
		m_pSnobeeManager->GetComponent<SnobeeManagerScript>()->RemoveWall(GetGameObject());
	}
}