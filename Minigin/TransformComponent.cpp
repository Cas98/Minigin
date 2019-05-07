#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent(const glm::vec3& pos)
	:mPosition(pos)
{
}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return mPosition;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
