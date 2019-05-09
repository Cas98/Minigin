#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>


void dae::SceneManager::Update()
{
	if (mpActiveScene) mpActiveScene->Update();
}

void dae::SceneManager::Render()
{
	if (mpActiveScene) mpActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::RemoveScene(const std::string& name)
{
	auto it = std::find_if(mScenes.begin(), mScenes.end(), [name](std::shared_ptr<Scene> scene)->bool
	{
		return scene->GetName() == name;
	});

	//id active scene == scene to remove set to nullptr 
	//else active scene will keep the removed scene alive
	if(mpActiveScene == *it)
	{
		mpActiveScene = nullptr;
	}

	if (it != mScenes.end())
	{
		mScenes.erase(it);
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(mScenes.begin(), mScenes.end(), [name](std::shared_ptr<Scene> scene)->bool
	{
		return scene->GetName() == name;
	});

	if(it != mScenes.end())
	{
		mpActiveScene = *it;
	}
}