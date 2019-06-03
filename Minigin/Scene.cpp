#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	object->SetScene(this);
	mObjects.push_back(object);
}

void dae::Scene::Update()
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render() const
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

void dae::Scene::SetActiveCamera(dae::CameraComponent* pActiveCamera)
{
	m_pActiveCamera = pActiveCamera;
}

dae::CameraComponent* dae::Scene::GetActiveCamera() const
{
	return m_pActiveCamera;
}