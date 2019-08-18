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
	//Subject* GetSubject() const;

	dae::Direction GetDirection() const;
	bool AreDiamondsAligned();

	void SetIsPushed(bool isPushed);
	bool GetIsPushed() const;

	void Break(bool isSnobeeManager = false);

	BlockScript(dae::GameObject* pGrid, dae::GameObject* pSnobeeManger = nullptr, bool canSpawnSnobee = false);
	~BlockScript();

private:
	bool IsObjectDiamond(glm::vec2 targetPos);

	//Subject* m_pSubject;
	dae::Direction m_Direction;
	bool m_IsPushed = false;
	bool m_CanSpawnSnobee;

	dae::GridComponent* m_pGridCompRef;
	dae::GameObject* m_pSnobeeManager;
};

