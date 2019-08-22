#pragma once
#include <ScriptComponent.h>
#include "Subject.h"
#include "helpers.h"
#include "GridComponent.h"

class BlockScript final: public dae::ScriptComponent
{

public:
	virtual void Init() override;
	virtual void Update() override;

	void MoveBlock(const dae::Direction& newDirection);

	dae::Direction GetDirection() const;
	bool AreDiamondsAligned();

	void SetIsPushed(bool isPushed);
	bool GetIsPushed() const;
	bool GetIsSnobeeAi() const;

	void Break(bool isSnobeeManager = false);

	BlockScript(dae::GameObject* pGrid, dae::GameObject* pSnobeeManger = nullptr, bool canSpawnSnobee = false, bool isSnobeeAi = true);
	~BlockScript();

private:
	bool IsObjectDiamond(glm::vec2 targetPos);

	dae::Direction m_Direction;
	bool m_IsPushed = false;
	bool m_CanSpawnSnobee;
	bool m_IsSnobeeAi;

	float m_ShowEggTime = 3.0f;
	bool m_IsEggShown = true;

	dae::GridComponent* m_pGridCompRef;
	dae::GameObject* m_pSnobeeManager;
};

