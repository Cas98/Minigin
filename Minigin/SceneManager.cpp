#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Renderer.h"


void dae::SceneManager::Update()
{
	if (mpActiveScene) mpActiveScene->RootUpdate();
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
		mScenes.erase(it);
		delete *it;
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(mScenes.begin(), mScenes.end(), [name](Scene* scene)->bool
	{
		return scene->GetName() == name;
	});

	if(it != mScenes.end())
	{
		//set render buffer
		Renderer::GetInstance().SetActiveRenderBuffer(mpActiveScene,*it);
		(*it)->RootInitialize();
		mpActiveScene = *it;
	}
}

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return mpActiveScene;
}