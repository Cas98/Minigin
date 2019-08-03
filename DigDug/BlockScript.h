#pragma once
#include <ScriptComponent.h>
#include "Subject.h"
#include "helpers.h"

class BlockScript final: public dae::ScriptComponent
{

public:
	virtual void Init() override;
	virtual void Update() override;

	void MoveBlock(const dae::Direction& newDirection);
	Subject* GetSubject() const;

	dae::Direction GetDirection() const;

	BlockScript();
	~BlockScript();

private:
	Subject* m_pSubject;
	dae::Direction m_Direction;
};

