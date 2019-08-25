#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent()
	:BaseComponent(dae::CompType::FPS)
{
	
}

void dae::FPSComponent::Update()
{
	//update queue
	if (m_PrevDeltaTimes.size() > size_t(m_AverageAmount))m_PrevDeltaTimes.pop_back();
	m_PrevDeltaTimes.push_front(Time::GetInstance().GetDeltaTime());

	//get average time
	float averageTime = 0.0f;
	std::for_each(m_PrevDeltaTimes.begin(), m_PrevDeltaTimes.end(), [&averageTime](float time) {averageTime += time; });
	averageTime /= m_PrevDeltaTimes.size();

	//print FPS
	std::string str;
	str += std::to_string((1.0 / averageTime)) + " FPS";

	GetGameObject()->GetComponent<TextComponent>()->SetText(str);
}