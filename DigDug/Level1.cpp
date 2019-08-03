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

Level1::Level1()
	:Scene("Level1")
{
}


Level1::~Level1()
{
}

void Level1::Initialize()
{
	//background
	auto background = new dae::GameObject({ 0.0f,-16.0f,0.0f });
	background->AddComponent(new dae::RenderComponent());
	background->AddComponent(new dae::TextureComponent("Images/Background.png"));

	Add(background);

	//Grid
	auto grid = new dae::GameObject({ 8.0f,248.0f,0.0f });
	grid->AddComponent(new dae::GridComponent(13, 15, 16.0f));

	Add(grid);

	//Wall
	auto wall = new dae::GameObject();
	wall->AddComponent(new dae::RenderComponent());
	wall->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	wall->SetTag("Wall");
	auto wallFSM = new dae::FSMComponent(new BlockIdleSate(wall, grid));
	wall->AddComponent(wallFSM);
	wall->AddComponent(new BlockScript());

	Add(wall);

	//Wall 2
	auto wall2 = new dae::GameObject();
	wall2->AddComponent(new dae::RenderComponent());
	wall2->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	wall2->SetTag("Wall");
	auto wallFSM2 = new dae::FSMComponent(new BlockIdleSate(wall2, grid));
	wall2->AddComponent(wallFSM2);
	wall2->AddComponent(new BlockScript());

	Add(wall2);

	//Player
	auto player = new dae::GameObject({0.0f,0.0f,1.0f},{0},{0.25f,0.25f});
	player->AddComponent(new dae::RenderComponent());
	player->AddComponent(new dae::TextureComponent("Block.jpg"));
	player->AddComponent(new dae::InputComponent(1));
	player->AddComponent(new PlayerScript(dae::Direction::Up));
	player->SetTag("Player");

	auto playerFSM = new dae::FSMComponent(new IdleState(player, grid));
	player->AddComponent(playerFSM);

	Add(player);

	grid->GetComponent<dae::GridComponent>()->SetGameObject(0, 0, player);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(5, 5, wall);
	grid->GetComponent<dae::GridComponent>()->SetGameObject(10, 5, wall2);

}

void Level1::Update()
{
	
}

