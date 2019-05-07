#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time : public Singleton<Time>
	{
	public:
		Time() = default;

		void Init();
		void Update();
		float GetDeltaTime();

		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	private:
		std::chrono::high_resolution_clock::time_point prevTime;
		float deltaTime{ 0.0f };
	};
}

