#pragma once
#include <ScriptComponent.h>
#include "helpers.h"

class GridScript final: public dae::ScriptComponent
{
public:
	GridScript();
	~GridScript();

	void ActivateWall(Direction direction);
	bool IsWallActive(Direction direction);
	void ActivateStars();

private:
	virtual void Init() override;
	virtual void Update() override;

	bool m_IsUpperWallActive = false, m_IsLowerWallActive = false, m_IsRightWallActive = false, m_IsLeftWallActive = false, m_IsStarActive = false;
	const float m_ResetTime = 2.0f;
	float m_UpperResetTime = 2.0f, m_LowerResetTime = 2.0f, m_RightResetTime = 2.0f, m_LeftResetTime = 2.0f, m_StarsResetTime = 5.0f;
	dae::GameObject* m_pBackground = nullptr, *m_pLeftWall = nullptr, *m_pRightWall = nullptr, *m_pUpperWall = nullptr, *m_pLowerWall = nullptr;
};

