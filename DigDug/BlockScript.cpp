#include "pch.h"
#include "BlockScript.h"
#include "GameObject.h"
#include "GridComponent.h"

BlockScript::BlockScript()
{
	//m_pSubject = new Subject();
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

bool BlockScript::AreDiamondsAligned(dae::GameObject* pGrid)
{
	auto gridComp = pGrid->GetComponent<dae::GridComponent>();
	auto gridCoords = gridComp->GetGameObjectPos(GetGameObject());
	std::vector<glm::vec2> directions = { {1,0},{0,1},{-1,0},{0,-1} };

	if(!gridComp)return false;

	for(size_t i{0}; i < directions.size(); ++i)
	{
		auto targetPos = gridCoords + directions[i];
		
		if(IsObjectDiamond(gridComp ,targetPos))
		{
			//option 1
			targetPos = gridCoords + (2.0f * directions[i]);
			
			if(IsObjectDiamond(gridComp, targetPos))
			{
				return true;
			}

			//option 2 
			targetPos = gridCoords - directions[i];

			if(IsObjectDiamond(gridComp, targetPos))
			{
				return true;
			}

			return false;
		}
	}

	return false;
}

bool BlockScript::IsObjectDiamond(dae::GridComponent* pGridComp, glm::vec2 targetPos)
{
	auto neighbouringObject = pGridComp->GetGameObject(int(targetPos.x), int(targetPos.y));

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