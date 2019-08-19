#pragma once
#include <ScriptComponent.h>
#include "helpers.h"
#include "Subject.h"
#include "SnobeeManagerScript.h"

class SnobeeScript final: public dae::ScriptComponent, public Observer
{
public:
	SnobeeScript(dae::Direction direction, dae::GameObject* pSnobeeManger, bool isAi = true);
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
	void Stun();
	void SetIsStunned(bool isStunned);
	bool GetIsStunned() const;
	bool GetIsAi() const;

	void OnNotify(dae::GameObject* gameObject, const std::string& message) override;

private:
	dae::Direction m_Direction;
	int m_RandomDirChange;

	bool m_IsPushed = false;
	bool m_IsStunned = false;
	bool m_IsAi;

	dae::GameObject* m_pSnobeeManager;
};

