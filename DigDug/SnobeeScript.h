#pragma once
#include <ScriptComponent.h>
#include "helpers.h"
#include "Subject.h"

class SnobeeScript final: public dae::ScriptComponent
{
public:
	SnobeeScript(dae::Direction direction);
	~SnobeeScript();

	virtual void Init() override;
	virtual void Update() override;

	dae::Direction GetDirection() const;
	void SetDirection(dae::Direction direction);

	void SetRandomDirChange();
	void DecrementRandomDirChange();
	int GetRandomDirChange() const;
	void Kill();
	void SetIsPushed(bool isPushed);
	bool GetIsPushed() const;

private:
	dae::Direction m_Direction;
	int m_RandomDirChange;

	bool m_IsPushed = false;
};

