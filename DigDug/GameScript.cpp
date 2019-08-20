#include "pch.h"
#include "GameScript.h"
#include "GameObject.h"
#include "PauseMenu.h"

GameScript::GameScript()
{
}

GameScript::~GameScript()
{
}

void GameScript::Init()
{
	m_InputRef = GetGameObject()->GetComponent<dae::InputComponent>();
}

void GameScript::Update()
{
	if(m_InputRef->KeyboardPressed(27))
	{
		auto scene = dae::SceneManager::GetInstance().GetScene("PauseMenu");
		if(scene)
		{
			static_cast<PauseMenu*>(scene)->SetCurrentLevel(GetGameObject()->GetScene()->GetName());
			dae::SceneManager::GetInstance().SetActiveScene("PauseMenu");
		}
		
	}
}