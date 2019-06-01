#pragma once
#include "ScriptComponent.h"
#include "InputComponent.h"
#include "TransformComponent.h"

class TestScript final: public dae::ScriptComponent
{
public:
	virtual void Init() override;
	virtual void Update() override;

private:
	dae::InputComponent* m_InputRef = nullptr;
	dae::TransformComponent* m_TransformRef = nullptr;
};

