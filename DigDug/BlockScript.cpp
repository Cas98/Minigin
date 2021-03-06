#include "pch.h"
#include "BlockScript.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "SnobeeManagerScript.h"
#include "SnobeeScript.h"
#include "SubjectComponent.h"
#include "GridScript.h"
#include "Time.h"
#include "TextureComponent.h"

BlockScript::BlockScript(dae::GameObject* pGrid, dae::GameObject* pSnobeeManger, bool canSpawnSnobee, bool isSnobeeAi)
	:m_CanSpawnSnobee(canSpawnSnobee), m_pSnobeeManager(pSnobeeManger), m_IsSnobeeAi(isSnobeeAi)
{
	m_pGridCompRef = pGrid->GetComponent<dae::GridComponent>();
}

BlockScript::~BlockScript()
{
}

void BlockScript::Init()
{
}

void BlockScript::Update()
{
	if(m_CanSpawnSnobee && m_IsEggShown)
	{
		m_ShowEggTime -= dae::Time::GetInstance().GetDeltaTime();
		if(m_ShowEggTime <= 0.0f)
		{
			GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture("Images/Wall.png");
			m_IsEggShown = false;
		}
	}
}

void BlockScript::MoveBlock(const Direction& newDirection)
{
	m_Direction = newDirection;
	SetIsPushed(true);
}

Direction BlockScript::GetDirection() const
{
	return m_Direction;
}

bool BlockScript::AreDiamondsAligned()
{
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
				m_pSnobeeManager->GetComponent<SnobeeManagerScript>()->StunSnobees();
				m_pGridCompRef->BaseComponent::GetGameObject()->GetComponent<GridScript>()->ActivateStars();
				return true;
			}

			//option 2 
			targetPos = gridCoords - directions[i];

			if(IsObjectDiamond(targetPos))
			{
				m_pSnobeeManager->GetComponent<SnobeeManagerScript>()->StunSnobees();
				m_pGridCompRef->BaseComponent::GetGameObject()->GetComponent<GridScript>()->ActivateStars();
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

bool BlockScript::GetIsSnobeeAi() const
{
	return m_IsSnobeeAi;
}

void BlockScript::Break(bool isSnobeeManager)
{
	//remove block from grid
	m_pGridCompRef->RemoveGameObject(GetGameObject());

	//destroy gameobject
	GetGameObject()->Destroy();

	if(m_CanSpawnSnobee && m_pSnobeeManager)
	{
		if(!isSnobeeManager)GetGameObject()->GetComponent <dae::SubjectComponent>()->Notify(GetGameObject(), "DestroyEgg");
		m_pSnobeeManager->GetComponent<SnobeeManagerScript>()->RemoveWall(GetGameObject());
	}
}