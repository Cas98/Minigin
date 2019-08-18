#include "pch.h"
#include "ScoreScript.h"
#include "GameObject.h"

ScoreScript::ScoreScript()
{
	
}

ScoreScript::~ScoreScript()
{
}

void ScoreScript::Init()
{
	m_pTextCompRef = GetGameObject()->GetComponent<dae::TextComponent>();
	m_pTextCompRef->SetText(std::to_string(0));
}

void ScoreScript::Update()
{
	
}

void ScoreScript::AddScore(int score)
{
	m_Score += score;
	m_pTextCompRef->SetText(std::to_string(m_Score));
}

void ScoreScript::OnNotify(dae::GameObject* gameObject, const std::string& message)
{
	if(message == "BreakWall")
	{
		AddScore(30);
	}
	else if (message == "KillStunnedSnobee")
	{
		AddScore(100);
	}
	else if (message == "KillSnobee")
	{
		AddScore(400);
	}
	else if (message == "DestroyEgg")
	{
		AddScore(500);
	}
	else if(message == "DiamondsAligned")
	{
		AddScore(3000);
	}
}