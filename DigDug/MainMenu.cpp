#include "pch.h"
#include "MainMenu.h"
#include "ButtonScript.h"
#include "GameObject.h"
#include <SDL.h>
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "Level1.h"
#include "PauseMenu.h"
#include "TextComponent.h"
#include "State.h"

class TestCommand : public dae::Command
{
public:
	void Execute() override { std::cout << "test" << std::endl; }
};

MainMenu::MainMenu()
	:Scene("MainMenu")
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
	//background
	auto background = new dae::GameObject({ 0.0f,0.0f,1.0f });
	background->AddComponent(new dae::RenderComponent());
	background->AddComponent(new dae::TextureComponent("Images/MainMenuBackground.png"));

	Add(background);

	//solo button
	auto soloFunction = []()
	{
		auto level = new Level1(GameMode::Solo);
		dae::SceneManager::GetInstance().AddScene(level);
		dae::SceneManager::GetInstance().SetActiveScene("Level1");
	};

	auto soloButton = new dae::GameObject({ 54.0f,-95.0f,0.1f });
	soloButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, soloFunction, "Images/SoloButton.png", "Images/SoloButtonSelected.png"));
	soloButton->AddComponent(new dae::InputComponent(0));
	soloButton->AddComponent(new dae::RenderComponent());
	soloButton->AddComponent(new dae::TextureComponent("Images/SoloButton.png"));
	Add(soloButton);

	//coop button
	auto coopFunction = []()
	{
		auto level = new Level1(GameMode::Coop);
		dae::SceneManager::GetInstance().AddScene(level);
		dae::SceneManager::GetInstance().SetActiveScene("Level1");
	};

	auto coopButton = new dae::GameObject({ 54.0f,-140.0f,0.1f });
	coopButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, coopFunction, "Images/CoopButton.png", "Images/CoopButtonSelected.png"));
	coopButton->AddComponent(new dae::InputComponent(0));
	coopButton->AddComponent(new dae::RenderComponent());
	coopButton->AddComponent(new dae::TextureComponent("Images/CoopButton.png"));
	Add(coopButton);

	//versus button
	auto versusFunction = []()
	{
		auto level = new Level1(GameMode::Versus);
		dae::SceneManager::GetInstance().AddScene(level);
		dae::SceneManager::GetInstance().SetActiveScene("Level1");
	};

	auto versusButton = new dae::GameObject({ 54.0f,-185.0f,0.1f });
	versusButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, versusFunction, "Images/VersusButton.png", "Images/VersusButtonSelected.png"));
	versusButton->AddComponent(new dae::InputComponent(0));
	versusButton->AddComponent(new dae::RenderComponent());
	versusButton->AddComponent(new dae::TextureComponent("Images/VersusButton.png"));
	Add(versusButton);

	//quit button
	auto quitFunction = []()
	{
		SDL_Event sdlEvent;
		sdlEvent.type = SDL_QUIT;
		SDL_PushEvent(&sdlEvent);
	};

	auto quitButton = new dae::GameObject({ 54.0f,-230.0f,0.1f });
	quitButton->AddComponent(new ButtonScript({ 114.0f,30.0f }, quitFunction, "Images/QuitButton.png", "Images/QuitButtonSelected.png"));
	quitButton->AddComponent(new dae::InputComponent(0));
	quitButton->AddComponent(new dae::RenderComponent());
	quitButton->AddComponent(new dae::TextureComponent("Images/QuitButton.png"));
	Add(quitButton);

	//Create Pause menu scene
	if (dae::SceneManager::GetInstance().GetScene("PauseMenu") == nullptr)
	{
		dae::SceneManager::GetInstance().AddScene(new PauseMenu());
	}

	//score
	m_pScore = new dae::GameObject({ 145.0f,-25.0f,0.0f });
	m_pScore->AddComponent(new dae::RenderComponent());
	m_pScore->AddComponent(new dae::TextureComponent());
	auto text = new dae::TextComponent("Lingua.otf", 20);
	m_pScore->AddComponent(text);
	text->SetText(std::to_string(m_Score));
	text->SetColor({ 10,10,250 });
	Add(m_pScore);

	auto highScore = new dae::GameObject({ 20.0f,-25.0f,0.0f });
	highScore->AddComponent(new dae::RenderComponent());
	highScore->AddComponent(new dae::TextureComponent());
	auto highScoreText = new dae::TextComponent("Lingua.otf", 20);
	highScore->AddComponent(highScoreText);
	highScoreText->SetText("HIGHSCORE - ");
	highScoreText->SetColor({ 10,10,250 });
	Add(highScore);
}

void MainMenu::Update()
{
	if(m_NeedsUpdate)
	{
		m_pScore->GetComponent<dae::TextComponent>()->SetText(std::to_string(m_Score));
		m_NeedsUpdate = false;
	}
}

void MainMenu::SetScore(int score)
{
	if(score > m_Score)
	{
		m_Score = score;
		m_NeedsUpdate = true;
	}
}
