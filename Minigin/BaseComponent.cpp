#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(CompType compType)
{
	m_CompType = compType;
}


void dae::BaseComponent::SetGameObject(GameObject* pObject)
{
	m_pGameObject = pObject;
}

dae::GameObject* dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}

dae::CompType dae::BaseComponent::GetComponentType()
{
	return m_CompType;
}