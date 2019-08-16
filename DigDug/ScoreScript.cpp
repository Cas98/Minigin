#include "pch.h"
#include "ScoreScript.h"


ScoreScript::ScoreScript()
{
}

ScoreScript::~ScoreScript()
{
}

void ScoreScript::Init()
{
	
}
void ScoreScript::Update()
{
	
}

void ScoreScript::AddScore(int score)
{
	m_Score += score;

	std::cout << "SCORE: " << m_Score << std::endl;
}

void ScoreScript::OnNotify(dae::GameObject* gameObject, const std::string& message)
{
	if(message == "BreakWall")
	{
		AddScore(30);
	}
}