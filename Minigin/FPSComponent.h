#pragma once
#include "BaseComponent.h"
#include <queue>

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent() override = default;

		void Update() override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		std::deque<float> m_PrevDeltaTimes;
		const int m_AverageAmount = 20;
	};
}

