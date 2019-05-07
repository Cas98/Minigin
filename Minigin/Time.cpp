#include "MiniginPCH.h"
#include "Time.h"


void dae::Time::Init()
{
	prevTime = std::chrono::high_resolution_clock::now();
};

void dae::Time::Update()
{
	auto t = std::chrono::high_resolution_clock::now();
	deltaTime = (float)(std::chrono::duration_cast<std::chrono::milliseconds>(t - prevTime).count() / 1000.0f);
	prevTime = t;
}

float dae::Time::GetDeltaTime()
{ 
	return deltaTime; 
};