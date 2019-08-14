#include "pch.h"
#include "Level1.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "GridComponent.h"
#include "InputComponent.h"
#include "FSMComponent.h"
#include "IdleState.h"
#include "BlockIdleSate.h"
#include "BlockScript.h"
#include "PlayerScript.h"
#include "SnobeeScript.h"
#include "SnobeeIdleState.h"
#include "SnobeeManagerScript.h"
#include "PlayerManagerScript.h"

Level1::Level1()
	:Scene("Level1")
{
}


Level1::~Level1()
{
}

void Level1::Initialize()
{
	std::vector<int> map = { 0,1,0,0,0,1,0,0,0,0,0,1,0,
							 0,1,0,1,1,1,0,1,1,2,0,1,0,
							 0,3,0,0,0,0,0,3,0,0,0,1,0,
							 0,1,1,1,1,1,1,1,0,1,1,1,0,
							 0,1,0,0,0,0,0,0,0,1,0,1,0,
							 0,1,0,1,1,2,1,1,1,1,0,1,0,
							 0,1,0,0,0,1,0,0,0,1,0,1,0,
							 0,1,1,1,0,3,0,1,1,1,0,3,0,
							 0,1,0,1,0,1,0,0,0,1,0,1,0,
							 0,3,0,1,0,1,0,1,3,1,0,0,0,
							 0,0,0,1,0,0,0,1,0,0,0,1,0,
							 0,1,0,1,1,1,0,1,0,1,1,1,0,
							 0,1,0,1,0,0,0,1,0,0,0,1,0,
						     0,1,0,2,0,1,3,1,1,1,0,1,0,
							 0,1,0,0,0,0,0,0,0,0,0,1,0 };
	//background
	auto background = new dae::GameObject({ 0.0f,-16.0f,0.0f });
	background->AddComponent(new dae::RenderComponent());
	background->AddComponent(new dae::TextureComponent("Images/Background.png"));

	Add(background);

	//Grid
	auto grid = new dae::GameObject({ 8.0f,248.0f,0.0f });
	grid->AddComponent(new dae::GridComponent(13, 15, 16.0f));

	Add(grid);

	//snobee manager
	auto snobeeManager = new dae::GameObject();
	snobeeManager->AddComponent(new SnobeeManagerScript(grid));
	Add(snobeeManager);

	//PlayerManager
	auto playerManager = new dae::GameObject();
	playerManager->AddComponent(new PlayerManagerScript(grid));
	Add(playerManager);

	for(int x{0}; x < 13; ++x)
	{
		for (int y{ 0 }; y < 15; ++y)
		{
			if(map[x + (y * 13)] == 1)
			{
				AddWall(x, y, grid, snobeeManager);
			}
			else if (map[x + (y * 13)] == 3)
			{
				AddWall(x, y, grid, snobeeManager, true);
			}
			else if(map[x + (y * 13)] == 2)
			{
				AddDiamond(x, y, grid);
			}
		}
	}

	////Wall
	//auto wall = new dae::GameObject();
	//wall->AddComponent(new dae::RenderComponent());
	//wall->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	//wall->SetTag("Wall");
	//auto wallFSM = new dae::FSMComponent(new BlockIdleSate(wall, grid));
	//wall->AddComponent(wallFSM);
	//wall->AddComponent(new BlockScript());

	//Add(wall);

	////Wall 2
	//auto wall2 = new dae::GameObject();
	//wall2->AddComponent(new dae::RenderComponent());
	//wall2->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	//wall2->SetTag("Wall");
	//auto wallFSM2 = new dae::FSMComponent(new BlockIdleSate(wall2, grid));
	//wall2->AddComponent(wallFSM2);
	//wall2->AddComponent(new BlockScript());

	//Add(wall2);

	////Diamond
	//auto diamond = new dae::GameObject();
	//diamond->AddComponent(new dae::RenderComponent());
	//diamond->AddComponent(new dae::TextureComponent("Images/Diamond.png"));
	//diamond->SetTag("Diamond");
	//auto diamondFSM = new dae::FSMComponent(new BlockIdleSate(diamond, grid));
	//diamond->AddComponent(diamondFSM);
	//diamond->AddComponent(new BlockScript());

	//Add(diamond);

	////Diamond 2
	//auto diamond2 = new dae::GameObject();
	//diamond2->AddComponent(new dae::RenderComponent());
	//diamond2->AddComponent(new dae::TextureComponent("Images/Diamond.png"));
	//diamond2->SetTag("Diamond");
	//auto diamondFSM2 = new dae::FSMComponent(new BlockIdleSate(diamond2, grid));
	//diamond2->AddComponent(diamondFSM2);
	//diamond2->AddComponent(new BlockScript());

	//Add(diamond2);

	////Diamond 3
	//auto diamond3 = new dae::GameObject();
	//diamond3->AddComponent(new dae::RenderComponent());
	//diamond3->AddComponent(new dae::TextureComponent("Images/Diamond.png"));
	//diamond3->SetTag("Diamond");
	//auto diamondFSM3 = new dae::FSMComponent(new BlockIdleSate(diamond3, grid));
	//diamond3->AddComponent(diamondFSM3);
	//diamond3->AddComponent(new BlockScript());

	//Add(diamond3);

	//Player
	auto player = new dae::GameObject({0.0f,0.0f,1.0f},{0},{0.25f,0.25f});
	player->AddComponent(new dae::RenderComponent());
	player->AddComponent(new dae::TextureComponent("Block.jpg"));
	player->AddComponent(new dae::InputComponent(1));
	player->AddComponent(new PlayerScript(dae::Direction::Up, playerManager));
	player->SetTag("Player");

	auto playerFSM = new dae::FSMComponent(new IdleState(player, grid));
	player->AddComponent(playerFSM);

	Add(player);

	////Player2
	//auto player2 = new dae::GameObject({ 0.0f,0.0f,1.0f }, { 0 }, { 0.25f,0.25f });
	//player2->AddComponent(new dae::RenderComponent());
	//player2->AddComponent(new dae::TextureComponent("Block.jpg"));
	//player2->AddComponent(new dae::InputComponent(2));
	//player2->AddComponent(new PlayerScript(dae::Direction::Up));
	//player2->SetTag("Player");

	//auto playerFSM2 = new dae::FSMComponent(new IdleState(player2, grid));
	//player2->AddComponent(playerFSM2);

	//Add(player2);

	//snobee

	/*for (int i{ 0 }; i < 7; ++i)
	{
		auto wall = new dae::GameObject();
		wall->AddComponent(new dae::RenderComponent());
		wall->AddComponent(new dae::TextureComponent("Images/Wall.png"));
		wall->SetTag("Wall");
		auto wallFSM = new dae::FSMComponent(new BlockIdleSate(wall, grid));
		wall->AddComponent(wallFSM);
		wall->AddComponent(new BlockScript());

		Add(wall);
		grid->GetComponent<dae::GridComponent>()->SetGameObject(1, i, wall);
	}

	auto snobee = new dae::GameObject();
	snobee->AddComponent(new dae::RenderComponent());
	snobee->AddComponent(new dae::TextureComponent("Images/Snobee.png"));
	snobee->AddComponent(new SnobeeScript(dae::Direction::Up));
	snobee->SetTag("Snobee");

	auto snobeeFSM = new dae::FSMComponent(new SnobeeIdleState(snobee, grid));
	snobee->AddComponent(snobeeFSM);

	Add(snobee);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(0, 5, snobee);*/

	/*for (int i{ 0 }; i < 4; ++i)
	{
		auto snobee = new dae::GameObject();
		snobee->AddComponent(new dae::RenderComponent());
		snobee->AddComponent(new dae::TextureComponent("Images/Snobee.png"));
		snobee->AddComponent(new SnobeeScript(dae::Direction::Up));
		snobee->SetTag("Snobee");

		auto snobeeFSM = new dae::FSMComponent(new SnobeeIdleState(snobee, grid));
		snobee->AddComponent(snobeeFSM);

		Add(snobee);
		grid->GetComponent<dae::GridComponent>()->SetGameObject(0, 7 + i, snobee);
	}*/



	grid->GetComponent<dae::GridComponent>()->SetGameObject(0, 0, player);
	/*grid->GetComponent<dae::GridComponent>()->SetGameObject(0, 1, wall);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(10, 5, wall2);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(3, 3, diamond);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(3, 5, diamond2);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(1, 3, diamond3);*/
	

}

void Level1::Update()
{
	
}

void Level1::AddWall(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, bool canSpawnSnobee)
{
	//Wall
	auto wall = new dae::GameObject();
	wall->AddComponent(new dae::RenderComponent());
	wall->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	wall->SetTag("Wall");
	auto wallFSM = new dae::FSMComponent(new BlockIdleSate(wall, pGrid));
	wall->AddComponent(wallFSM);
	wall->AddComponent(new BlockScript(pGrid, pSnobeeManager, canSpawnSnobee));

	Add(wall);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, wall);

	if(canSpawnSnobee)//add to snobee manager
	{
		pSnobeeManager->GetComponent<SnobeeManagerScript>()->AddWall(wall);
	}
}

void Level1::AddSnobee(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager)
{
	auto snobee = new dae::GameObject();
	snobee->AddComponent(new dae::RenderComponent());
	snobee->AddComponent(new dae::TextureComponent("Images/Snobee.png"));
	snobee->AddComponent(new SnobeeScript(dae::Direction::Up, pSnobeeManager));
	snobee->SetTag("Snobee");

	auto snobeeFSM = new dae::FSMComponent(new SnobeeIdleState(snobee, pGrid));
	snobee->AddComponent(snobeeFSM);

	Add(snobee);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, snobee);
}

void Level1::AddDiamond(int x, int y, dae::GameObject* pGrid)
{
	auto diamond = new dae::GameObject();
	diamond->AddComponent(new dae::RenderComponent());
	diamond->AddComponent(new dae::TextureComponent("Images/Diamond.png"));
	diamond->SetTag("Diamond");
	auto diamondFSM = new dae::FSMComponent(new BlockIdleSate(diamond, pGrid));
	diamond->AddComponent(diamondFSM);
	diamond->AddComponent(new BlockScript(pGrid));

	Add(diamond);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, diamond);
}