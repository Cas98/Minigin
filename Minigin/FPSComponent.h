#pragma once
#include "BaseComponent.h"
#include <queue>

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent() = default;
		~FPSComponent() = default;

		void Update() override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		std::deque<float> mPrevDeltaTimes;
		const int mAverageAmount = 20;
	};
}

