#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent(const float x, const  float y, const  float z)
{
	transform.SetPosition(x,y,z);
}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return transform.GetPosition();
}

void dae::TransformComponent::SetPosition(const float x, const  float y, const  float z)
{
	transform.SetPosition(x, y, z);
}
