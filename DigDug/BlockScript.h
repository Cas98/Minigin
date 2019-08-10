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
	bool AreDiamondsAligned(dae::GameObject* pGrid);

	void SetIsPushed(bool isPushed);
	bool GetIsPushed() const;

	BlockScript();
	~BlockScript();

private:
	bool IsObjectDiamond(dae::GridComponent* pGridComp , glm::vec2 targetPos);

	//Subject* m_pSubject;
	dae::Direction m_Direction;
	bool m_IsPushed = false;
};

