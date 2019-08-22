#include "pch.h"
#include "SnobeeManagerScript.h"
#include "GameObject.h"
#include "BlockScript.h"
#include "SnobeeIdleState.h"
#include "SnobeeScript.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "FSMComponent.h"
#include "Renderer.h"
#include "SubjectComponent.h"

SnobeeManagerScript::SnobeeManagerScript(dae::GameObject* pGrid, dae::GameObject* pScore)
{
	m_pGridCompRef = pGrid->GetComponent<dae::GridComponent>();
	m_pScoreScriptRef = pScore->GetComponent<ScoreScript>();
}

SnobeeManagerScript::~SnobeeManagerScript()
{
}

void SnobeeManagerScript::Init()
{
}

void SnobeeManagerScript::Update()
{
	if(m_NumberOfActiveSnobees < m_MaxActiveSnobees)
	{
		if(m_pWallsThatSpawnSnobees.size() > 0)//spawn snobee
		{
			auto coords = m_pGridCompRef->GetGameObjectPos(m_pWallsThatSpawnSnobees[m_pWallsThatSpawnSnobees.size() - 1]);
			auto wallScript = m_pWallsThatSpawnSnobees[m_pWallsThatSpawnSnobees.size() - 1]->GetComponent<BlockScript>();
			wallScript->Break(true);
			bool isAi = wallScript->GetIsSnobeeAi();
			if (m_IsNextSnobeePlayer)
			{
				isAi = false;
				m_IsNextSnobeePlayer = false;
			}
			SpawnSnobee(coords.x, coords.y, isAi);
			m_NumberOfActiveSnobees++;
			
		}
		else if(m_NumberOfActiveSnobees == 0)//if no more snobees left game is won
		{
			GetGameObject()->GetComponent<dae::SubjectComponent>()->Notify(GetGameObject(), "EndGame");
		}
	}
}

void SnobeeManagerScript::AddWall(dae::GameObject* pWall)
{
	m_pWallsThatSpawnSnobees.push_back(pWall);

	//add ui
	float screenWidth = float(dae::Renderer::GetInstance().GetWindowSize().x);
	auto lifeUi = new dae::GameObject({ screenWidth - (8.0f * (m_pWallsThatSpawnSnobees.size() - 1)),0.0f,1.0f });
	lifeUi->AddComponent(new dae::RenderComponent());
	lifeUi->AddComponent(new dae::TextureComponent("Images/SnobeeLife.png"));
	GetGameObject()->GetScene()->Add(lifeUi);
	m_pLifeUIs.push_back(lifeUi);
}

void SnobeeManagerScript::RemoveWall(dae::GameObject* pWall)
{
	auto it = std::find(m_pWallsThatSpawnSnobees.begin(), m_pWallsThatSpawnSnobees.end(), pWall);
	if (it != m_pWallsThatSpawnSnobees.end())
	{
		m_pWallsThatSpawnSnobees.erase(it);
	}
}

void SnobeeManagerScript::SpawnSnobee(int x, int y, bool isAi)
{
	auto snobee = new dae::GameObject();
	snobee->AddComponent(new dae::RenderComponent());
	auto script = new SnobeeScript(dae::Direction::Up, GetGameObject(), isAi);

	std::string path{ "Images/Snobee.png" };
	if (!script->GetIsAi()) path = "Images/SnobeeYellow.png";
	snobee->AddComponent(new dae::TextureComponent(path));

	//if snobee is player controlled add input component
	if(!script->GetIsAi())
	{
		snobee->AddComponent(new dae::InputComponent(1));
	}

	auto subjectComp = new dae::SubjectComponent();
	subjectComp->AddObserver(m_pScoreScriptRef);
	snobee->AddComponent(subjectComp);

	snobee->AddComponent(script);
	snobee->SetTag("Snobee");

	auto snobeeFSM = new dae::FSMComponent(new SnobeeIdleState(snobee, m_pGridCompRef->BaseComponent::GetGameObject()));
	snobee->AddComponent(snobeeFSM);

	GetGameObject()->GetScene()->AddThreaded(snobee);
	m_pGridCompRef->SetGameObject(x, y, snobee);

	auto subject = GetGameObject()->GetComponent<dae::SubjectComponent>();
	if (subject)
	{
		subject->AddObserver(script);
	}

	//remove ui
	if (m_pLifeUIs.size() > 0)
	{
		m_pLifeUIs[m_pLifeUIs.size() - 1]->Destroy();
		m_pLifeUIs.pop_back();
	}
}

void SnobeeManagerScript::DecrementActiveSnobees()
{
	m_NumberOfActiveSnobees--;
}

void SnobeeManagerScript::StunSnobees()
{
	auto subject = GetGameObject()->GetComponent<dae::SubjectComponent>();
	if(subject)
	{
		subject->Notify(GetGameObject(), "Stun");
	}
}

void SnobeeManagerScript::RemoveObserver(SnobeeScript* pSnobeeObserver)
{
	auto subject = GetGameObject()->GetComponent<dae::SubjectComponent>();
	if (subject)
	{
		subject->RemoveObserver(pSnobeeObserver);
	}
}

void SnobeeManagerScript::SetIsNextSnobeePlayer(bool isPlayer)
{
	m_IsNextSnobeePlayer = isPlayer;
}