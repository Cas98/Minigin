// DigDug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "Level1.h"


int main(int , char **)
{
	dae::Minigin engine;
	engine.Initialize();

	auto scene = new Level1();
	dae::SceneManager::GetInstance().AddScene(scene);
	dae::SceneManager::GetInstance().SetActiveScene("Level1");

	engine.Run();
	return 0;
}
