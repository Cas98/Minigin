#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"


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

