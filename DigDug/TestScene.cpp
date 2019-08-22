#include "pch.h"
#include "TestScene.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Command.h"
#include "InputComponent.h"
#include "TestScript.h"
#include "Time.h"



TestScene::TestScene()
 :Scene("TestScene")
{
}


//TestScene::~TestScene()
//{
//}


void TestScene::Initialize()
{
	//////background
	//auto object0 = new dae::GameObject(glm::vec3(0.0f, 0.0f, 0.0f));
	//object0->AddComponent(new dae::RenderComponent());
	//object0->AddComponent(new dae::TextureComponent("background.jpg"));
	//dae::InputComponent* comp = new dae::InputComponent(1);
	//comp->MapKey(dae::ControllerButton::ButtonA, 'A', std::make_shared<TestCommand>(TestCommand()), dae::KeyState::Released);
	//object0->AddComponent(comp);
	//Add(object0);

	//////logo
	//for (int i{ 0 }; i < 10; ++i)
	//{
	//	auto object1 = new dae::GameObject(glm::vec3(216.0f + i, -180.0f - i, 0.0f), 90.0f);
	//	object1->AddComponent(new dae::RenderComponent());
	//	object1->AddComponent(new dae::TextureComponent("logo.png"));
	//	Add(object1);
	//}

	//////text
	//auto object2 = new dae::GameObject(glm::vec3(80.0f, -50.0f, 0.0f));
	//object2->AddComponent(new dae::RenderComponent());
	//object2->AddComponent(new dae::TextureComponent());
	//object2->AddComponent(new dae::TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	//Add(object2);

	//////FPS
	//auto object3 = new dae::GameObject(glm::vec3(10.0f, -10.0f, 0.0f));
	//object3->AddComponent(new dae::RenderComponent());
	//object3->AddComponent(new dae::TextureComponent());
	//object3->AddComponent(new dae::TextComponent("Lingua.otf", 36));
	//object3->AddComponent(new dae::FPSComponent());
	//Add(object3);

	//////test object
	//auto testObj = new dae::GameObject(glm::vec3(0, -100.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f));
	//testObj->AddComponent(new dae::RenderComponent());
	//testObj->AddComponent(new dae::TextureComponent("Block.jpg"));
	//testObj->AddComponent(new dae::InputComponent(0));
	//testObj->AddComponent(new TestScript());
	//Add(testObj);

	//auto testObj2 = new dae::GameObject(glm::vec3(0, -100.0f, 0.0f), 45.0f, glm::vec2(0.5f, 0.5f));
	//testObj2->AddComponent(new dae::RenderComponent());
	//testObj2->AddComponent(new dae::TextureComponent("Block.jpg"));
	//Add(testObj2);

	//auto testObj3 = new dae::GameObject(glm::vec3(0, -100.0f, 0.0f), 45.0f, glm::vec2(0.5f, 0.5f));
	//testObj3->AddComponent(new dae::RenderComponent());
	//testObj3->AddComponent(new dae::TextureComponent("Block.jpg"));
	////testObj3->AddComponent(new dae::TextureComponent("Block.jpg"));
	//Add(testObj3);

	//testObj->AddChild(testObj2);
	//testObj2->AddChild(testObj3);

	//testObj2->Destroy();
}

void TestScene::Update()
{
	if (sec <= 0.0f) sec = 10.0f;
	sec -= dae::Time::GetInstance().GetDeltaTime();

	if (sec <= 0.0f) 
		dae::SceneManager::GetInstance().SetActiveScene("Level1");
}