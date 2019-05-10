// DigDug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Scene.h"


int main(int , char **)
{
	dae::Minigin engine;
	engine.Initialize();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	dae::SceneManager::GetInstance().SetActiveScene("Demo");

	//background
	auto object0 = std::make_shared<dae::GameObject>();
	object0->AddComponent(new dae::RenderComponent());
	object0->AddComponent(new dae::TextureComponent("background.jpg"));
	object0->AddComponent(new dae::TransformComponent(0.0f, 0.0f, 0.0f));
	scene.Add(object0);

	//logo
	auto object1 = std::make_shared<dae::GameObject>();
	object1->AddComponent(new dae::RenderComponent());
	object1->AddComponent(new dae::TextureComponent("logo.png"));
	object1->AddComponent(new dae::TransformComponent(216.0f, 180.0f, 0.0f));
	scene.Add(object1);

	//text
	auto object2 = std::make_shared<dae::GameObject>();
	object2->AddComponent(new dae::RenderComponent());
	object2->AddComponent(new dae::TextureComponent());
	object2->AddComponent(new dae::TransformComponent(80.0f, 50.0f, 0.0f));
	object2->AddComponent(new dae::TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	scene.Add(object2);

	//FPS
	auto object3 = std::make_shared<dae::GameObject>();
	object3->AddComponent(new dae::RenderComponent());
	object3->AddComponent(new dae::TextureComponent());
	object3->AddComponent(new dae::TransformComponent(10.0f, 10.0f, 0.0f));
	object3->AddComponent(new dae::TextComponent("Lingua.otf", 36));
	object3->AddComponent(new dae::FPSComponent());
	scene.Add(object3);


	
	engine.Run();
	return 0;
}
