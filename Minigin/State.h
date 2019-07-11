#pragma once
#include "InputComponent.h"

namespace dae
{
	class FSMComponent;

	class State
	{
	public:
		State() = default;
		~State() = default;

	private:
		friend FSMComponent;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual void Update() = 0;
		virtual State* HandleInput(InputComponent* input) = 0;
	};
}

