#include "pch.h"
#include "GridScript.h"
#include "Time.h"


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
		break;

	case dae::Direction::Up:
		m_IsUpperWallActive = true;
		break;

	case dae::Direction::Right:
		m_IsRightWallActive = true;
		break;

	case dae::Direction::Left:
		m_IsLeftWallActive = true;
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
		}
	}

}
