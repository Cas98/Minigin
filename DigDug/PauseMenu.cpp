#include "pch.h"
#include "PauseMenu.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "ButtonScript.h"
#include <SDL.h>

PauseMenu::PauseMenu()
	:Scene("PauseMenu")
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Initialize()
{
	//background
	auto background = new dae::GameObject({ 0.0f,0.0f,1.0f });
	background->AddComponent(new dae::RenderComponent());
	background->AddComponent(new dae::TextureComponent("Images/MainMenuBackground.png"));

	Add(background);

	//coop button
	std::string str = m_CurrentLevelName;
	auto continueFunction = [str]()
	{
		dae::SceneManager::GetInstance().SetActiveScene(str);
	};

	auto continueButton = new dae::GameObject({ 54.0f,-85.0f,0.1f });
	continueButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, continueFunction, "Images/ContinueButton.png", "Images/ContinueButtonSelected.png"));
	continueButton->AddComponent(new dae::InputComponent(0));
	continueButton->AddComponent(new dae::RenderComponent());
	continueButton->AddComponent(new dae::TextureComponent("Images/ContinueButton.png"));
	Add(continueButton);

	//versus button
	auto MainMenuFunction = [str]()
	{
		dae::SceneManager::GetInstance().RemoveScene(str);
		dae::SceneManager::GetInstance().SetActiveScene("MainMenu");
	};

	auto MainMenuButton = new dae::GameObject({ 54.0f,-130.0f,0.1f });
	MainMenuButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, MainMenuFunction, "Images/MainMenuButton.png", "Images/MainMenuButtonSelected.png"));
	MainMenuButton->AddComponent(new dae::InputComponent(0));
	MainMenuButton->AddComponent(new dae::RenderComponent());
	MainMenuButton->AddComponent(new dae::TextureComponent("Images/MainMenuButton.png"));
	Add(MainMenuButton);

	//quit button
	auto quitFunction = []()
	{
		SDL_Event sdlEvent;
		sdlEvent.type = SDL_QUIT;
		SDL_PushEvent(&sdlEvent);
	};

	auto quitButton = new dae::GameObject({ 54.0f,-175.0f,0.1f });
	quitButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, quitFunction, "Images/QuitButton.png", "Images/QuitButtonSelected.png"));
	quitButton->AddComponent(new dae::InputComponent(0));
	quitButton->AddComponent(new dae::RenderComponent());
	quitButton->AddComponent(new dae::TextureComponent("Images/QuitButton.png"));
	Add(quitButton);

}

void PauseMenu::Update()
{
	
}

void PauseMenu::SetCurrentLevel(const std::string& levelName)
{
	m_CurrentLevelName = levelName;
}