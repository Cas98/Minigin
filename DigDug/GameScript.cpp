#include "pch.h"
#include "GameScript.h"
#include "GameObject.h"
#include "PauseMenu.h"
#include "Level2.h"
#include "Level3.h"
#include "MainMenu.h"
#include "Time.h"

GameScript::GameScript(int nextLevel, GameMode gameMode, dae::GameObject* pPlayerManager, dae::GameObject* pScore)
	:m_Nextlevel(nextLevel), m_GameMode(gameMode)
{
	m_pPlayerManagerRef = pPlayerManager->GetComponent<PlayerManagerScript>();
	m_pScore = pScore->GetComponent<ScoreScript>();
}

GameScript::~GameScript()
{
}

void GameScript::Init()
{
	m_pInputRef = GetGameObject()->GetComponent<dae::InputComponent>();
}

void GameScript::Update()
{
	if(m_pInputRef->KeyboardPressed(27))
	{
		auto scene = dae::SceneManager::GetInstance().GetScene("PauseMenu");
		if(scene)
		{
			static_cast<PauseMenu*>(scene)->SetCurrentLevel(GetGameObject()->GetScene()->GetName());
			dae::SceneManager::GetInstance().SetActiveScene("PauseMenu");
		}
		
	}

	m_Time -= dae::Time::GetInstance().GetDeltaTime();

	if(m_Time <= 0.0f)
	{
		EndGame();
	}
}

void GameScript::OnNotify(dae::GameObject* , const std::string& message)
{
	if(message == "EndGame")
	{
		EndGame();
	}

	if (message == "GameOver")
	{
		auto menu = static_cast<MainMenu*>(dae::SceneManager::GetInstance().GetScene("MainMenu"));
		menu->SetScore(m_pScore->GetScore());
		dae::SceneManager::GetInstance().SetActiveScene("MainMenu", true);
	}
}

void GameScript::EndGame()
{
	if(m_Time >= 0)
	{
		m_pScore->AddScore(int(m_Time) * 10);
	}

	dae::Scene* level;
	MainMenu* menu;
	switch (m_Nextlevel)
	{
	case 0:
		menu = static_cast<MainMenu*>(dae::SceneManager::GetInstance().GetScene("MainMenu"));
		menu->SetScore(m_pScore->GetScore());
		dae::SceneManager::GetInstance().SetActiveScene("MainMenu", true);
		break;

	case 2:
		level = new Level2(m_GameMode, m_pPlayerManagerRef->GetPlayerLives(), m_pScore->GetScore());
		dae::SceneManager::GetInstance().AddScene(level);
		dae::SceneManager::GetInstance().SetActiveScene("Level2", true);
		break;

	case 3:
		level = new Level3(m_GameMode, m_pPlayerManagerRef->GetPlayerLives(), m_pScore->GetScore());
		dae::SceneManager::GetInstance().AddScene(level);
		dae::SceneManager::GetInstance().SetActiveScene("Level3", true);
		break;
	}
}