#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <thread>

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

	while (m_pObjectsThread.size() > 0)
	{
		m_pObjectsThread[0]->Destroy();
	}

	DeleteObjects();
};

void dae::Scene::Add(GameObject* object)
{
	object->SetScene(this);
	//mObjects.push_back(object);
	m_pAddedObjects.push_back(object);
}

void dae::Scene::AddThreaded(GameObject* object)
{
	object->SetScene(this);
	m_pAddedObjectsThread.push_back(object);
}

void dae::Scene::Remove(dae::GameObject* object)
{
	auto it = std::find(mObjects.begin(), mObjects.end(), object);
	if (it != mObjects.end())
	{
		m_pObjectsToDelete.push_back(*it);
		mObjects.erase(it);
	}

	it = std::find(m_pObjectsThread.begin(), m_pObjectsThread.end(), object);
	if (it != m_pObjectsThread.end())
	{
		m_pObjectsToDelete.push_back(*it);
		m_pObjectsThread.erase(it);
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
	auto threadUpdate = [](std::vector<GameObject*> pObjectsThread)
	{
		for (auto gameObject : pObjectsThread)
		{
			gameObject->Update();
			//std::cout << "Update gameobject threaded" << std::endl;
		}
	};

	std::thread thread(threadUpdate, m_pObjectsThread);

	for(auto gameObject : mObjects)
	{
		gameObject->Update();
		//std::cout << "Update gameobject" << std::endl;
	}

	thread.join();

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

	for (size_t i{ 0 }; i < m_pAddedObjectsThread.size(); ++i)
	{
		m_pObjectsThread.push_back(m_pAddedObjectsThread[i]);
	}

	m_pAddedObjects.clear();
	m_pAddedObjectsThread.clear();
}
