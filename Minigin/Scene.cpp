#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <thread>

unsigned int dae::Scene::m_IdCounter = 0;

dae::Scene::Scene(const std::string& name)
: mName(name)
{
}

dae::Scene::~Scene()
{
	while(m_pObjects.size() > 0)
	{
		m_pObjects[0]->Destroy();
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
	m_pAddedObjects.push_back(object);
}

void dae::Scene::AddThreaded(GameObject* object)
{
	object->SetScene(this);
	m_pAddedObjectsThread.push_back(object);
}

void dae::Scene::Remove(dae::GameObject* object)
{
	//add gameobject to the delete vector
	auto it = std::find(m_pObjects.begin(), m_pObjects.end(), object);
	if (it != m_pObjects.end())
	{
		m_pObjectsToDelete.push_back(*it);
		m_pObjects.erase(it);
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
	//update objects on thread vector on different thread
	auto threadUpdate = [](std::vector<GameObject*> pObjectsThread)
	{
		for (auto gameObject : pObjectsThread)
		{
			gameObject->Update();
		}
	};

	std::thread thread(threadUpdate, m_pObjectsThread);

	//update gameobjects
	for(auto gameObject : m_pObjects)
	{
		gameObject->Update();
	}

	thread.join();

	Update();
	//delete the objects in the delete vector
	DeleteObjects();
	//add the objects from the add vector to active object list
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
		m_pObjects.push_back(m_pAddedObjects[i]);
	}

	for (size_t i{ 0 }; i < m_pAddedObjectsThread.size(); ++i)
	{
		m_pObjectsThread.push_back(m_pAddedObjectsThread[i]);
	}

	m_pAddedObjects.clear();
	m_pAddedObjectsThread.clear();
}
