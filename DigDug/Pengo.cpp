#include "pch.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "MainMenu.h"

int main(int , char **)
{
	dae::Minigin engine;
	engine.Initialize();

	auto mainMenu = new MainMenu();
	dae::SceneManager::GetInstance().AddScene(mainMenu);
	dae::SceneManager::GetInstance().SetActiveScene("MainMenu");

	engine.Run();
	return 0;
}
