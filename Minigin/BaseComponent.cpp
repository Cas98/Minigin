#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(CompType compType)
{
	m_CompType = compType;
}


void dae::BaseComponent::SetGameObject(GameObject* object)
{
	m_GameObject = object;
}

dae::GameObject* dae::BaseComponent::GetGameObject() const
{
	return m_GameObject;
}

dae::CompType dae::BaseComponent::GetComponentType()
{
	return m_CompType;
}