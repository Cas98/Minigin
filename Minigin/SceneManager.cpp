#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Renderer.h"


void dae::SceneManager::Update()
{
	if (mpActiveScene) mpActiveScene->RootUpdate();
	if(m_pSceneToRemove)
	{
		RemoveScene(m_pSceneToRemove->GetName());
		m_pSceneToRemove = nullptr;
	}
}

void  dae::SceneManager::Destroy()
{
	for(auto scene : mScenes)
	{
		delete scene;
	}
}

void dae::SceneManager::AddScene(Scene* scene)
{
	if (scene)
	{
		auto it = std::find_if(mScenes.begin(), mScenes.end(), [scene](Scene* s)->bool
		{
			return scene->GetName() == s->GetName();
		});

		if (it == mScenes.end())
		{
			mScenes.push_back(scene);
		}
		else
		{
			std::cout << "There already is a scene with name " << scene->GetName() << std::endl;
			delete scene;
		}
	}
}

void dae::SceneManager::RemoveScene(const std::string& name)
{
	auto it = std::find_if(mScenes.begin(), mScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	if(mpActiveScene == *it)
	{
		mpActiveScene = nullptr;
	}

	if (it != mScenes.end())
	{
		//remove render buffer
		Renderer::GetInstance().RemoveRenderBuffer(*it);
		Scene* pScene = *it;
		mScenes.erase(it);
		delete pScene;
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name, bool deleteCurrentScene)
{
	auto it = std::find_if(mScenes.begin(), mScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	if(it != mScenes.end())
	{
		
		//set render buffer
		Renderer::GetInstance().SetActiveRenderBuffer(mpActiveScene,*it);
		if (deleteCurrentScene) m_pSceneToRemove = mpActiveScene;
		mpActiveScene = *it;
		(*it)->RootInitialize();
	}
}

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return mpActiveScene;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name)
{
	auto it = std::find_if(mScenes.begin(), mScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	if (it != mScenes.end())
	{
		return *it;
	}

	return nullptr;
}