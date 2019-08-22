#pragma once
#include "BaseComponent.h"
#include "State.h"

namespace dae
{
	class FSMComponent final : public dae::BaseComponent
	{
	public:
		FSMComponent(State* pStartState);
		~FSMComponent() override;

		void Init() override;
		void Update() override;
	
	private:
		State* m_pCurrentState = nullptr;
		InputComponent* m_pInputRef = nullptr;
	};
}

