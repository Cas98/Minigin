#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"


void dae::FPSComponent::Update()
{
	//update queue
	if (mPrevDeltaTimes.size() > mAverageAmount)mPrevDeltaTimes.pop_back();
	mPrevDeltaTimes.push_back(Time::GetInstance().GetDeltaTime());

	//get average time
	float averageTime = 0.0f;
	std::for_each(mPrevDeltaTimes.begin(), mPrevDeltaTimes.end(), [&averageTime](float time) {averageTime += time; });
	averageTime /= mPrevDeltaTimes.size();

	//print FPS
	std::string str;
	str += std::to_string((1.0 / averageTime)) + " FPS";

	GetParentObject()->GetComponent<TextComponent>()->SetText(str);
}