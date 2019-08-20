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
#include "GridScript.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GameScript.h"

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
	////background
	auto background = new dae::GameObject({ 0.0f,-16.0f,0.1f });
	background->AddComponent(new dae::RenderComponent());
	background->AddComponent(new dae::TextureComponent("Images/Background.png"));

	GetGameObject()->GetScene()->Add(background);

	//game manager
	auto gameManager = new dae::GameObject();
	gameManager->AddComponent(new GameScript());
	gameManager->AddComponent(new dae::InputComponent(0));
	GetGameObject()->GetScene()->Add(gameManager);

	//Grid
	auto grid = new dae::GameObject({ 8.0f,248.0f,0.0f });
	grid->AddComponent(new dae::GridComponent(13, 15, 16.0f));
	grid->AddComponent(new GridScript());

	GetGameObject()->GetScene()->Add(grid);

	//score
	auto score = new dae::GameObject({ 104.0f,1.0f,0.0f });
	score->AddComponent(new dae::RenderComponent());
	score->AddComponent(new dae::TextureComponent());
	score->AddComponent(new dae::TextComponent("Lingua.otf", 20));
	score->AddComponent(new ScoreScript());
	GetGameObject()->GetScene()->Add(score);

	//snobee manager
	auto snobeeManager = new dae::GameObject();
	snobeeManager->AddComponent(new SnobeeManagerScript(grid, score));
	snobeeManager->AddComponent(new dae::SubjectComponent());
	GetGameObject()->GetScene()->Add(snobeeManager);

	//PlayerManager
	auto playerManager = new dae::GameObject();
	playerManager->AddComponent(new PlayerManagerScript(grid));
	GetGameObject()->GetScene()->Add(playerManager);

	int playerIndex = 0;

	for (int x{ 0 }; x < 13; ++x)
	{
		for (int y{ 0 }; y < 15; ++y)
		{
			if (map[x + (y * 13)] == 1)
			{
				AddWall(x, y, grid, snobeeManager, score);
			}
			else if (map[x + (y * 13)] == 2)
			{
				AddDiamond(x, y, grid, snobeeManager, score);
			}
			else if (map[x + (y * 13)] == 3)
			{
				AddWall(x, y, grid, snobeeManager, score, true);
			}
			else if(map[x + (y * 13)] == 4)
			{
				AddPlayer(x, y, grid, playerManager, score, playerIndex);
				playerIndex++;
			}
			else if (map[x + (y * 13)] == 5)
			{
				AddWall(x, y, grid, snobeeManager, score, true, false);
			}
		}
	}

	
}

void LevelLoaderScript::AddWall(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore, bool canSpawnSnobee, bool isSnobeeAi)
{
	//Wall
	auto wall = new dae::GameObject();
	wall->AddComponent(new dae::RenderComponent());
	wall->AddComponent(new dae::TextureComponent("Images/Wall.png"));
	wall->SetTag("Wall");

	auto wallFSM = new dae::FSMComponent(new BlockIdleSate(wall, pGrid));
	wall->AddComponent(wallFSM);
	wall->AddComponent(new BlockScript(pGrid, pSnobeeManager, canSpawnSnobee, isSnobeeAi));

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

//void LevelLoaderScript::AddSnobee(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager)
//{
//	auto snobee = new dae::GameObject();
//	snobee->AddComponent(new dae::RenderComponent());
//	snobee->AddComponent(new dae::TextureComponent("Images/Snobee.png"));
//	snobee->AddComponent(new SnobeeScript(dae::Direction::Up, pSnobeeManager));
//	snobee->SetTag("Snobee");
//
//	auto snobeeFSM = new dae::FSMComponent(new SnobeeIdleState(snobee, pGrid));
//	snobee->AddComponent(snobeeFSM);
//
//	GetGameObject()->GetScene()->Add(snobee);
//	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, snobee);
//}

void LevelLoaderScript::AddDiamond(int x, int y, dae::GameObject* pGrid, dae::GameObject* pSnobeeManager, dae::GameObject* pScore)
{
	auto diamond = new dae::GameObject();
	diamond->AddComponent(new dae::RenderComponent());
	diamond->AddComponent(new dae::TextureComponent("Images/Diamond.png"));
	diamond->SetTag("Diamond");
	auto diamondFSM = new dae::FSMComponent(new BlockIdleSate(diamond, pGrid));
	diamond->AddComponent(diamondFSM);
	diamond->AddComponent(new BlockScript(pGrid, pSnobeeManager));

	auto subjectComp = new dae::SubjectComponent();
	subjectComp->AddObserver(pScore->GetComponent<ScoreScript>());
	diamond->AddComponent(subjectComp);

	GetGameObject()->GetScene()->Add(diamond);
	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, diamond);
}

void LevelLoaderScript::AddPlayer(int x, int y, dae::GameObject* pGrid, dae::GameObject* pPlayerManager, dae::GameObject* pScore, int playerIndex)
{
	//Player
	auto player = new dae::GameObject({ 0.0f,0.0f,1.0f }, { 0 }, { 0.25f,0.25f });
	player->AddComponent(new dae::RenderComponent());
	player->AddComponent(new dae::TextureComponent("Block.png"));
	player->AddComponent(new dae::InputComponent(playerIndex));
	player->AddComponent(new PlayerScript(dae::Direction::Up, pPlayerManager,{x,y}));
	player->SetTag("Player");

	auto subjectComp = new dae::SubjectComponent();
	subjectComp->AddObserver(pScore->GetComponent<ScoreScript>());
	player->AddComponent(subjectComp);

	auto playerFSM = new dae::FSMComponent(new IdleState(player, pGrid));
	player->AddComponent(playerFSM);

	GetGameObject()->GetScene()->Add(player);

	pGrid->GetComponent<dae::GridComponent>()->SetGameObject(x, y, player);
}