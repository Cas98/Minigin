#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent()
{
}


void dae::BaseComponent::SetParentObject(GameObject* object)
{
	mParentObject = object;
}

dae::GameObject* dae::BaseComponent::GetParentObject() const
{
	return mParentObject;
}