#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"


dae::GameObject::~GameObject()
{
	for (size_t i{ 0 }; i < mComponents.size(); ++i)
	{
		delete mComponents[i];
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


