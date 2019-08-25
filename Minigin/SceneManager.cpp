#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Renderer.h"


void dae::SceneManager::Update()
{
	if (m_pActiveScene) m_pActiveScene->RootUpdate();
	if(m_pSceneToRemove)
	{
		RemoveScene(m_pSceneToRemove->GetName());
		m_pSceneToRemove = nullptr;
	}
}

void  dae::SceneManager::Destroy()
{
	for(auto scene : m_pScenes)
	{
		delete scene;
	}
}

void dae::SceneManager::AddScene(Scene* scene)
{
	if (scene)
	{
		//check if there is no scene with current name
		auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [scene](Scene* s)->bool
		{
			return scene->GetName() == s->GetName();
		});

		//if not add scene
		if (it == m_pScenes.end())
		{
			m_pScenes.push_back(scene);
		}
		else//delete scene
		{
			std::cout << "There already is a scene with name " << scene->GetName() << std::endl;
			delete scene;
		}
	}
}

void dae::SceneManager::RemoveScene(const std::string& name)
{
	//find scene
	auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	if(m_pActiveScene == *it)
	{
		m_pActiveScene = nullptr;
	}

	//if found remove
	if (it != m_pScenes.end())
	{
		//remove render buffer
		Renderer::GetInstance().RemoveRenderBuffer(*it);
		Scene* pScene = *it;
		m_pScenes.erase(it);
		delete pScene;
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name, bool deleteCurrentScene)
{
	//find scene
	auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	//if found set actiive
	if(it != m_pScenes.end())
	{
		//set render buffer
		Renderer::GetInstance().SetActiveRenderBuffer(m_pActiveScene,*it);
		if (deleteCurrentScene) m_pSceneToRemove = m_pActiveScene;
		m_pActiveScene = *it;
		(*it)->RootInitialize();
	}
}

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return m_pActiveScene;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name)
{
	auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	if (it != m_pScenes.end())
	{
		return *it;
	}

	return nullptr;
}