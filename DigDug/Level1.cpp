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
#include "ScoreScript.h"
#include "SubjectComponent.h"
#include "LevelLoaderScript.h"
#include "Time.h"

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
							 2,1,0,1,1,1,0,1,1,2,0,1,0,
							 0,3,0,0,0,0,0,3,0,0,0,1,0,
							 2,1,1,1,1,1,1,1,0,1,1,1,0,
							 2,1,0,0,0,0,0,0,0,1,0,1,0,
							 0,1,0,1,1,2,1,1,1,1,0,1,0,
							 0,1,0,0,0,1,0,0,0,1,0,1,0,
							 0,1,1,1,0,3,0,1,1,1,0,3,0,
							 0,1,0,1,0,1,4,0,0,1,0,1,0,
							 0,3,0,1,0,1,0,1,3,1,0,0,0,
							 0,0,0,1,0,0,0,1,0,0,0,1,0,
							 0,1,0,1,1,1,0,1,0,1,1,1,0,
							 0,1,0,1,0,0,0,1,0,0,0,1,0,
						     0,1,0,2,0,1,3,1,1,1,0,1,0,
							 0,1,0,0,0,0,0,0,0,0,0,1,0 };

	auto levelLoader = new dae::GameObject();
	auto script = new LevelLoaderScript();
	levelLoader->AddComponent(script);
	Add(levelLoader);
	script->Load(map);


	
}

void Level1::Update()
{
	/*if (sec <= 0.0f) sec = 10.0f;
	sec -= dae::Time::GetInstance().GetDeltaTime();

	if (sec <= 0.0f)
		dae::SceneManager::GetInstance().SetActiveScene("TestScene");*/
}

