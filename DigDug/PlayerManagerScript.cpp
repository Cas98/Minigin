#include "pch.h"
#include "PlayerManagerScript.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "InputComponent.h"
#include "PlayerScript.h"
#include "FSMComponent.h"
#include "IdleState.h"
#include "GameObject.h"
#include "GridComponent.h"

PlayerManagerScript::PlayerManagerScript(dae::GameObject* pGrid)
	:m_pGrid(pGrid)
{
}


PlayerManagerScript::~PlayerManagerScript()
{
}

void PlayerManagerScript::Init()
{
	for(int i{0}; i < m_PlayerLives; ++i)
	{
		auto lifeUi = new dae::GameObject({ i * 16.0f,0.0f,1.0f });
		lifeUi->AddComponent(new dae::RenderComponent());
		lifeUi->AddComponent(new dae::TextureComponent("Images/PengoLife.png"));
		GetGameObject()->GetScene()->Add(lifeUi);
		m_pLifeUIs.push_back(lifeUi);
	}
}

void PlayerManagerScript::Update()
{
	
}

void PlayerManagerScript::RespawnPlayer()
{
	if(m_PlayerLives > 0)
	{
		m_PlayerLives--;
		//remove ui
		m_pLifeUIs[m_pLifeUIs.size() - 1]->Destroy();
		m_pLifeUIs.pop_back();

		//respawn player
		auto player = new dae::GameObject({ 0.0f,0.0f,1.0f }, { 0 }, { 0.25f,0.25f });
		player->AddComponent(new dae::RenderComponent());
		player->AddComponent(new dae::TextureComponent("Block.jpg"));
		player->AddComponent(new dae::InputComponent(1));
		player->AddComponent(new PlayerScript(dae::Direction::Up, GetGameObject()));
		player->SetTag("Player");

		auto playerFSM = new dae::FSMComponent(new IdleState(player, m_pGrid));
		player->AddComponent(playerFSM);

		GetGameObject()->GetScene()->Add(player);

		glm::vec2 coords{ 0.0f,0.0f };
		auto grid = m_pGrid->GetComponent<dae::GridComponent>();
		while(grid->GetGameObject(coords.x, coords.y) != nullptr)
		{
			coords.y += 1;
		}
		grid->SetGameObject(coords.x, coords.y, player);
	}
	else//game lost
	{
		
	}
}
