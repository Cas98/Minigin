#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name)
: mName(name)
{
}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	object->SetScene(this);
	mObjects.push_back(object);
}

void dae::Scene::RootInitialize()
{
	Initialize();
}

void dae::Scene::RootUpdate()
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}

	Update();
}

void dae::Scene::RootRender() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

std::string dae::Scene::GetName()
{
	return mName;
}


