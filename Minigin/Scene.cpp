#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name)
: mName(name)
{
}

dae::Scene::~Scene()
{
	while(mObjects.size() > 0)
	{
		mObjects[0]->Destroy();
	}
};

void dae::Scene::Add(GameObject* object)
{
	object->SetScene(this);
	mObjects.push_back(object);
}

void dae::Scene::Remove(dae::GameObject* object)
{
	auto it = std::find(mObjects.begin(), mObjects.end(), object);
	if (it != mObjects.end())
	{
		mObjects.erase(it);
	}
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


