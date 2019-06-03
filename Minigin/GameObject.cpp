#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject(glm::vec3 pos, float rotation, glm::vec2 scale)
{
	//every gameobject has a transform
	AddComponent(new dae::TransformComponent(pos, rotation, scale));
}

dae::GameObject::~GameObject()
{
	//delete components
	for (size_t i{ 0 }; i < mComponents.size(); ++i)
	{
		delete mComponents[i];
	}

	//delete children objects
	for (size_t i{ 0 }; i < mChildren.size(); ++i)
	{
		delete mChildren[i];
	}
}

void dae::GameObject::Update()
{
	if(!m_IsInit)
	{
		for (size_t i{ 0 }; i < mComponents.size(); ++i)
		{
			mComponents[i]->Init();
		}
		m_IsInit = true;
	}

	for (size_t i{ 0 }; i < mComponents.size(); ++i)
	{
		mComponents[i]->Update();
	}
}

void dae::GameObject::Render() const
{
	for (size_t i{ 0 }; i < mComponents.size(); ++i)
	{
		mComponents[i]->Render();
	}
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	component->SetParentObject(this);
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


void dae::GameObject::AddChild(GameObject* gameObject)
{
	mChildren.push_back(gameObject);
	gameObject->mpParent = this;
}

void dae::GameObject::RemoveChild(dae::GameObject* gameObject)
{
	auto it = std::find(mChildren.begin(), mChildren.end(), gameObject);
	if(it != mChildren.end())
	{
		mChildren.erase(it);
	}
}

void dae::GameObject::SetScene(dae::Scene* scene)
{
	m_pScene = scene;
}

dae::Scene* dae::GameObject::GetScene()
{
	return m_pScene;
}

