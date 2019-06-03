#include "MiniginPCH.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "Scene.h"


dae::CameraComponent::CameraComponent(bool setActive)
{
	if(setActive)
	{
		SetActive();
	}
}

void dae::CameraComponent::Init()
{
	m_pTransformRef = GetParentObject()->GetComponent<dae::TransformComponent>();
	m_pSceneRef = GetParentObject()->GetScene();

	if(m_IsActive)
	{
		SetActive();
	}
}

void dae::CameraComponent::SetActive()
{
	m_IsActive = true;
	if (m_pSceneRef != nullptr)
	{
		dae::CameraComponent* camera = m_pSceneRef->GetActiveCamera();
		if (camera != nullptr) camera->SetInActive();
	}
	if(m_pSceneRef != nullptr) m_pSceneRef->SetActiveCamera(this);
}

void dae::CameraComponent::SetInActive()
{
	m_IsActive = false;
}

bool dae::CameraComponent::IsActive()
{
	return m_IsActive;
}

dae::TransformComponent* dae::CameraComponent::GetTransform() const
{
	return m_pTransformRef;
}