#include "pch.h"
#include "GridScript.h"
#include "Time.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "RenderComponent.h"

GridScript::GridScript()
{
}


GridScript::~GridScript()
{
}

void GridScript::Init()
{
	
}

void GridScript::ActivateWall(dae::Direction direction)
{
	switch(direction)
	{
	case dae::Direction::Down:
		m_IsLowerWallActive = true;
		m_pLowerWall = new dae::GameObject({ 0.0f,-264.0f,0.1f });
		m_pLowerWall->AddComponent(new dae::RenderComponent());
		m_pLowerWall->AddComponent(new dae::TextureComponent("Images/WallHorizontal.png"));
		GetGameObject()->GetScene()->Add(m_pLowerWall);
		break;

	case dae::Direction::Up:
		m_IsUpperWallActive = true;
		m_pUpperWall = new dae::GameObject({ 0.0f,-16.0f,0.1f });
		m_pUpperWall->AddComponent(new dae::RenderComponent());
		m_pUpperWall->AddComponent(new dae::TextureComponent("Images/WallHorizontal.png"));
		GetGameObject()->GetScene()->Add(m_pUpperWall);
		break;

	case dae::Direction::Right:
		m_IsRightWallActive = true;
		m_pRightWall = new dae::GameObject({ 216.0f,-16.0f,0.1f });
		m_pRightWall->AddComponent(new dae::RenderComponent());
		m_pRightWall->AddComponent(new dae::TextureComponent("Images/WallVertical.png"));
		GetGameObject()->GetScene()->Add(m_pRightWall);
		break;

	case dae::Direction::Left:
		m_IsLeftWallActive = true;
		m_pLeftWall = new dae::GameObject({ 0.0f,-16.0f,0.1f });
		m_pLeftWall->AddComponent(new dae::RenderComponent());
		m_pLeftWall->AddComponent(new dae::TextureComponent("Images/WallVertical.png"));
		GetGameObject()->GetScene()->Add(m_pLeftWall);
		break;
	}
}

bool GridScript::IsWallActive(dae::Direction direction)
{
	switch (direction)
	{
	case dae::Direction::Down:
		return m_IsLowerWallActive;
		break;

	case dae::Direction::Up:
		return m_IsUpperWallActive;
		break;

	case dae::Direction::Right:
		return m_IsRightWallActive;
		break;

	case dae::Direction::Left:
		return m_IsLeftWallActive;
		break;
	}
}

void GridScript::ActivateStars()
{
	m_IsStarActive = true;
	m_pBackground = new dae::GameObject({ 0.0f,-16.0f,0.1f });
	m_pBackground->AddComponent(new dae::RenderComponent());
	m_pBackground->AddComponent(new dae::TextureComponent("Images/BackgroundStars.png"));
	GetGameObject()->GetScene()->Add(m_pBackground);
}

void GridScript::Update()
{
	//update upper wall
	if(m_IsUpperWallActive)
	{
		m_UpperResetTime -= dae::Time::GetInstance().GetDeltaTime();
		if (m_UpperResetTime <= 0.0f)
		{
			m_UpperResetTime = m_ResetTime;
			m_IsUpperWallActive = false;
			m_pUpperWall->Destroy();
		}
	}

	//update lower wall
	if (m_IsLowerWallActive)
	{
		m_LowerResetTime -= dae::Time::GetInstance().GetDeltaTime();
		if (m_LowerResetTime <= 0.0f)
		{
			m_LowerResetTime = m_ResetTime;
			m_IsLowerWallActive = false;
			m_pLowerWall->Destroy();
		}
	}

	//update right wall
	if (m_IsRightWallActive)
	{
		m_RightResetTime -= dae::Time::GetInstance().GetDeltaTime();
		if (m_RightResetTime <= 0.0f)
		{
			m_RightResetTime = m_ResetTime;
			m_IsRightWallActive = false;
			m_pRightWall->Destroy();
		}
	}

	//update left wall
	if (m_IsLeftWallActive)
	{
		m_LeftResetTime -= dae::Time::GetInstance().GetDeltaTime();
		if (m_LeftResetTime <= 0.0f)
		{
			m_LeftResetTime = m_ResetTime;
			m_IsLeftWallActive = false;
			m_pLeftWall->Destroy();
		}
	}

	//stars
	if(m_IsStarActive)
	{
		m_StarsResetTime -= dae::Time::GetInstance().GetDeltaTime();
		if(m_StarsResetTime <= 0.0f)
		{
			m_pBackground->Destroy();
			m_IsStarActive = false;
		}
	}

}
