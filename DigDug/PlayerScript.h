#pragma once
#include <ScriptComponent.h>
#include "helpers.h"

class PlayerScript final : public dae::ScriptComponent
{
public:
	PlayerScript(dae::Direction diretcion);
	~PlayerScript();

	virtual void Init() override;
	virtual void Update() override;

	dae::Direction GetDirection() const;
	void SetDirection(dae::Direction diretcion);

private:
	dae::Direction m_Direction;
};

