#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Scene.h"
#include "Time.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//background
	auto object0 = std::make_shared<GameObject>();
	object0->AddComponent(new RenderComponent());
	object0->AddComponent(new TextureComponent("background.jpg"));
	object0->AddComponent(new TransformComponent(glm::vec3(0.0f,0.0f,0.0f)));
	scene.Add(object0);

	//logo
	auto object1 = std::make_shared<GameObject>();
	object1->AddComponent(new RenderComponent());
	object1->AddComponent(new TextureComponent("logo.png"));
	object1->AddComponent(new TransformComponent(glm::vec3(216.0f, 180.0f, 0.0f)));
	scene.Add(object1);

	//text
	auto object2 = std::make_shared<GameObject>();
	object2->AddComponent(new RenderComponent());
	object2->AddComponent(new TextureComponent());
	object2->AddComponent(new TransformComponent(glm::vec3(80.0f, 50.0f, 0.0f)));
	object2->AddComponent(new TextComponent("Programming 4 Assignment","Lingua.otf",36));
	scene.Add(object2);

	//FPS
	auto object3 = std::make_shared<GameObject>();
	object3->AddComponent(new RenderComponent());
	object3->AddComponent(new TextureComponent());
	object3->AddComponent(new TransformComponent(glm::vec3(10.0f, 10.0f, 0.0f)));
	object3->AddComponent(new TextComponent("Lingua.otf", 36));
	object3->AddComponent(new FPSComponent());
	scene.Add(object3);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	Time::GetInstance().Init();

	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();

		bool doContinue = true;
		float lag = 0.0f;
		while (doContinue)
		{
			lag += time.GetDeltaTime();
			time.Update();
			
			doContinue = input.ProcessInput();

			while (lag > float(time.msPerFrame / 1000.0f))
			{
				sceneManager.Update();
				lag -= float(1.0f / time.msPerFrame);
			}

			renderer.Render();
		}
	}

	Cleanup();
}
