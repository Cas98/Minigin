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

class TestCommand : public dae::Command
{
public:
	void Execute() override { std::cout << "test" << std::endl; }
};

TestScene::TestScene()
 :Scene("TestScene")
{
}


TestScene::~TestScene()
{
}


void TestScene::Initialize()
{
	//background
	auto object0 = std::make_shared<dae::GameObject>(glm::vec3(0.0f, 0.0f, 0.0f));
	object0->AddComponent(new dae::RenderComponent());
	object0->AddComponent(new dae::TextureComponent("background.jpg"));
	dae::InputComponent* comp = new dae::InputComponent(1);
	comp->MapKey(dae::ControllerButton::ButtonA, 'A', std::make_shared<TestCommand>(TestCommand()), dae::KeyState::Released);
	object0->AddComponent(comp);
	Add(object0);

	//logo
	for (int i{ 0 }; i < 1; ++i)
	{
		auto object1 = std::make_shared<dae::GameObject>(glm::vec3(216.0f + i, -180.0f - i, 0.0f), 90.0f);
		object1->AddComponent(new dae::RenderComponent());
		object1->AddComponent(new dae::TextureComponent("logo.png"));
		Add(object1);
	}

	//text
	auto object2 = std::make_shared<dae::GameObject>(glm::vec3(80.0f, -50.0f, 0.0f));
	object2->AddComponent(new dae::RenderComponent());
	object2->AddComponent(new dae::TextureComponent());
	object2->AddComponent(new dae::TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	Add(object2);

	//FPS
	auto object3 = std::make_shared<dae::GameObject>(glm::vec3(10.0f, -10.0f, 0.0f));
	object3->AddComponent(new dae::RenderComponent());
	object3->AddComponent(new dae::TextureComponent());
	object3->AddComponent(new dae::TextComponent("Lingua.otf", 36));
	object3->AddComponent(new dae::FPSComponent());
	Add(object3);

	//test object
	auto testObj = std::make_shared<dae::GameObject>(glm::vec3(0, -100.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f));
	testObj->AddComponent(new dae::RenderComponent());
	testObj->AddComponent(new dae::TextureComponent("Block.jpg"));
	testObj->AddComponent(new dae::InputComponent(0));
	testObj->AddComponent(new TestScript());
	Add(testObj);

	auto testObj2 = std::make_shared<dae::GameObject>(glm::vec3(0, -100.0f, 0.0f), 45.0f, glm::vec2(0.5f, 0.5f));
	testObj2->AddComponent(new dae::RenderComponent());
	testObj2->AddComponent(new dae::TextureComponent("Block.jpg"));
	Add(testObj2);

	auto testObj3 = std::make_shared<dae::GameObject>(glm::vec3(0, -100.0f, 0.0f), 45.0f, glm::vec2(0.5f, 0.5f));
	testObj3->AddComponent(new dae::RenderComponent());
	testObj3->AddComponent(new dae::TextureComponent("Block.jpg"));
	//testObj3->AddComponent(new dae::TextureComponent("Block.jpg"));
	Add(testObj3);

	testObj->AddChild(testObj2.get());
	testObj2->AddChild(testObj3.get());
}

void TestScene::Update()
{
	
}