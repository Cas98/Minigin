// DigDug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "Level1.h"
#include "TestScene.h"
#include "MainMenu.h"


int main(int , char **)
{
	dae::Minigin engine;
	engine.Initialize();

	//auto scene = new Level1();
	auto mainMenu = new MainMenu();
	dae::SceneManager::GetInstance().AddScene(mainMenu);
	dae::SceneManager::GetInstance().SetActiveScene("MainMenu");

	engine.Run();
	return 0;
}
