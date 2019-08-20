#pragma once
#include <ScriptComponent.h>
#include "InputComponent.h"

class GameScript : public dae::ScriptComponent
{
public:
	GameScript();
	~GameScript();

private:
	virtual void Init() override;
	virtual void Update() override;

	dae::InputComponent* m_InputRef;

};

