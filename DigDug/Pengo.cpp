// DigDug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "TestScene.h"


int main(int , char **)
{
	dae::Minigin engine;
	engine.Initialize();

	auto scene = new TestScene();
	dae::SceneManager::GetInstance().AddScene(scene);
	dae::SceneManager::GetInstance().SetActiveScene("TestScene");

	engine.Run();
	return 0;
}
