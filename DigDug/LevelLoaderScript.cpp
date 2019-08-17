#include "pch.h"
#include "LevelLoaderScript.h"
#include "SnobeeManagerScript.h"
#include "SubjectComponent.h"
#include "ScoreScript.h"
#include "BlockScript.h"
#include "BlockIdleSate.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "FSMComponent.h"
#include "SnobeeIdleState.h"
#include "SnobeeScript.h"
#include "PlayerManagerScript.h"
#include "IdleState.h"
#include "PlayerScript.h"

LevelLoaderScript::LevelLoaderScript()
{
}


LevelLoaderScript::~LevelLoaderScript()
{
}

void LevelLoaderScript::Init()
{
	
}

void LevelLoaderScript::Update()
{
	
}

void LevelLoaderScript::Load(const std::vector<int>& map)
{
	//background
	auto background = new dae::GameObject({ 0.0f,-16.0f,0.1f });
	background->AddComponent(new dae::RenderComponent());
	background->AddComponent(new dae::TextureComponent("Images/Background.png"));

	GetGameObject()->GetScene()->Add(background);

	//Grid
	auto grid = new dae::GameObject({ 8.0f,248.0f,0.0f });
	grid->AddComponent(new dae::GridComponent(13, 15, 16.0f));

	GetGameObject()->GetScene()->Add(grid);

	//snobee manager
	auto snobeeManager = new dae::GameObject();
	snobeeManager->AddComponent(new SnobeeManagerScript(grid));
	GetGameObject()->GetScene()->Add(snobeeManager);

	//PlayerManager
	auto playerManager = new dae::GameObject();
	playerManager->AddComponent(new PlayerManagerScript(grid));
	GetGameObject()->GetScene()->Add(playerManager);

	//score
	auto score = new dae::GameObject();
	score->AddComponent(new ScoreScript());
	GetGameObject()->GetScene()->Add(score);

	for (int x{ 0 }; x < 13; ++x)
	{
		for (int y{ 0 }; y < 15; ++y)
		{
			if (map[x + (y * 13)] == 1)
			{
				AddWall(x, y, grid, snobeeManager, score);
			}
			else if (map[x + (y * 13)] == 3)
			{
				AddWall(x, y, grid, snobeeManager, score, true);
			}
			else if (map[x + (y * 13)] == 2)
			{
				AddDiamond(x, y, grid);
			}
		}
	}

	//Player
	auto player = new dae::GameObject({ 0.0f,0.0f,1.0f }, { 0 }, { 0.25f,0.25f });
	player->AddComponent(new dae::RenderComponent());
	player->AddComponent(new dae::TextureComponent("Block.jpg"));
	player->AddComponent(new dae::InputComponent(1));
	player->AddComponent(new PlayerScript(dae::Direction::Up, playerManager));
	player->SetTag("Player");

	auto playerFSM = new dae::FSMComponent(new IdleState(player, grid));
	player->AddComponent(playerFSM);

	GetGameObject()->GetScene()->Add(player);

	grid->GetComponent<dae::GridComponent>()->SetGameObject(0, 0, player);
}

void LevelLoaderScript::AddWall(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore, bool canSpawnSnobee)
{
	//Wall
	auto wall = new dae::GameObject();
	wall->AddComponent(new dae::RenderComponent());
	wall->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	wall->SetTag("Wall");

	auto wallFSM = new dae::FSMComponent(new BlockIdleSate(wall, pGrid));
	wall->AddComponent(wallFSM);
	wall->AddComponent(new BlockScript(pGrid, pSnobeeManager, canSpawnSnobee));

	auto subjectComp = new dae::SubjectComponent();
	subjectComp->AddObserver(pScore->GetComponent<ScoreScript>());
	wall->AddComponent(subjectComp);

	GetGameObject()->GetScene()->Add(wall);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, wall);

	if (canSpawnSnobee)//add to snobee manager
	{
		pSnobeeManager->GetComponent<SnobeeManagerScript>()->AddWall(wall);
	}
}

void LevelLoaderScript::AddSnobee(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager)
{
	auto snobee = new dae::GameObject();
	snobee->AddComponent(new dae::RenderComponent());
	snobee->AddComponent(new dae::TextureComponent("Images/Snobee.png"));
	snobee->AddComponent(new SnobeeScript(dae::Direction::Up, pSnobeeManager));
	snobee->SetTag("Snobee");

	auto snobeeFSM = new dae::FSMComponent(new SnobeeIdleState(snobee, pGrid));
	snobee->AddComponent(snobeeFSM);

	GetGameObject()->GetScene()->Add(snobee);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, snobee);
}

void LevelLoaderScript::AddDiamond(int x, int y, dae::GameObject* pGrid)
{
	auto diamond = new dae::GameObject();
	diamond->AddComponent(new dae::RenderComponent());
	diamond->AddComponent(new dae::TextureComponent("Images/Diamond.png"));
	diamond->SetTag("Diamond");
	auto diamondFSM = new dae::FSMComponent(new BlockIdleSate(diamond, pGrid));
	diamond->AddComponent(diamondFSM);
	diamond->AddComponent(new BlockScript(pGrid));

	GetGameObject()->GetScene()->Add(diamond);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, diamond);
}