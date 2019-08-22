#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ScriptComponent : public dae::BaseComponent
	{
	public:
		ScriptComponent()
			:BaseComponent(dae::CompType::Script){};
		virtual ~ScriptComponent() override = default;

		virtual void Init() override = 0;
		virtual void Update() override = 0;

		ScriptComponent(const ScriptComponent &) = delete;
		ScriptComponent(ScriptComponent &&) = delete;
		ScriptComponent & operator= (const ScriptComponent &) = delete;
		ScriptComponent & operator= (const ScriptComponent &&) = delete;
	};
}

