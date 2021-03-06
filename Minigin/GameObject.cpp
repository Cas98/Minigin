#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <algorithm>

dae::GameObject::GameObject(glm::vec3 pos, float rotation, glm::vec2 scale)
{
	//every gameobject has a transform
	m_pTransform = new dae::TransformComponent(pos, rotation, scale);
	AddComponent(m_pTransform);
}

void dae::GameObject::Destroy()
{
	//Remove gameobject from scene
	auto scene = GetScene();

	if (scene)
	{
		scene->Remove(this);
	}
}

dae::GameObject::~GameObject()
{
	//delete components
	for (auto component : mComponents)
	{
		delete component;
	}
}

void dae::GameObject::Update()
{
	//if not initialized initialize;
	if(!m_IsInit)
	{
		for (auto component : mComponents)
		{
			component->Init();
		}
		m_IsInit = true;
	}

	for (auto component : mComponents)
	{
		component->Update();
	}
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	//every gameobject only can have 1 of each type of component
	if(HasComponent(component))
	{
		std::cout << "ERROR: Can't give game object same component twice \n";
		return;
	}

	component->SetGameObject(this);
	mComponents.push_back(component);
	if(m_IsInit) component->Init();
}

void dae::GameObject::RemoveComponent(BaseComponent* component)
{
	auto it = std::find(mComponents.begin(), mComponents.end(), component);
	if (it != mComponents.end())
	{
		mComponents.erase(it);
	}
}

bool dae::GameObject::HasComponent(BaseComponent* component) const
{
	auto it = std::find_if(mComponents.begin(), mComponents.end(), [component](BaseComponent* comp)
	{
		return component->GetComponentType() == comp->GetComponentType();
	});

	if(it != mComponents.end())
	{
		return true;
	}

	return false;
}

void dae::GameObject::SetScene(dae::Scene* scene)
{
	m_pScene = scene;
}

dae::Scene* dae::GameObject::GetScene()
{
	return m_pScene;
}

dae::TransformComponent* dae::GameObject::GetTransformComponent() const
{
	return m_pTransform;
}

std::string dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::SetTag(const std::string& newTag)
{
	m_Tag = newTag;
}