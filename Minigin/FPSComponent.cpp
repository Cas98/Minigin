#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

void dae::FPSComponent::Update()
{
	std::string str;
	str += std::to_string((1.0 / Time::GetInstance().GetDeltaTime())) + " FPS";

	GetParentObject()->GetComponent<TextComponent>()->SetText(str);
}