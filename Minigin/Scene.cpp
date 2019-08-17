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

	DeleteObjects();
};

void dae::Scene::Add(GameObject* object)
{
	object->SetScene(this);
	//mObjects.push_back(object);
	m_pAddedObjects.push_back(object);
}

void dae::Scene::Remove(dae::GameObject* object)
{
	auto it = std::find(mObjects.begin(), mObjects.end(), object);
	m_pObjectsToDelete.push_back(*it);
	if (it != mObjects.end())
	{
		mObjects.erase(it);
	}
}

void dae::Scene::RootInitialize()
{
	if (!m_IsInizialized)
	{
		Initialize();
		AddObjects();
		m_IsInizialized = true;
	}
}

void dae::Scene::RootUpdate()
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}

	Update();
	DeleteObjects();
	AddObjects();
}



std::string dae::Scene::GetName()
{
	return mName;
}

void dae::Scene::DeleteObjects()
{
	for(size_t i{0}; i < m_pObjectsToDelete.size();++i)
	{
		delete m_pObjectsToDelete[i];
	}

	m_pObjectsToDelete.clear();
}

void dae::Scene::AddObjects()
{
	for (size_t i{ 0 }; i < m_pAddedObjects.size(); ++i)
	{
		mObjects.push_back(m_pAddedObjects[i]);
	}

	m_pAddedObjects.clear();
}
