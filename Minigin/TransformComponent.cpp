#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent(const float x, const  float y, const  float z, const float rotation, const float scaleX, const float scaleY)
{
	transform.SetTransform({ x,-y,z }, {scaleX, scaleY}, rotation);
}

dae::TransformComponent::TransformComponent(const glm::vec3& pos, const float rotation, const glm::vec2& scale)
{
	transform.SetTransform({pos.x,-pos.y,pos.z}, scale, rotation);
}

//pos
const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return transform.GetPosition();
}

void dae::TransformComponent::SetPosition(const float x, const  float y, const  float z)
{
	transform.SetPosition(x, -y, z);
}

void dae::TransformComponent::SetPosition(const glm::vec3& pos)
{
	transform.SetPosition({ pos.x,-pos.y,pos.z });
}

void dae::TransformComponent::Translate(const float x, const  float y, const  float z)
{
	auto position = transform.GetPosition();
	position.x += x;
	position.y -= y;
	position.z += z;

	transform.SetPosition(position);
}

void dae::TransformComponent::Translate(const glm::vec3& pos)
{
	auto position = transform.GetPosition();
	position.x += pos.x;
	position.y -= pos.y;
	position.z += pos.z;

	transform.SetPosition(position);
};

//scale
const glm::vec2& dae::TransformComponent::GetScale() const
{
	return transform.GetScale();
}

void dae::TransformComponent::SetScale(const float x, const  float y)
{
	transform.SetScale(x, y);
}

void dae::TransformComponent::SetScale(const glm::vec2& scale)
{
	transform.SetScale(scale);
}

//rotate
const float dae::TransformComponent::GetRotation() const
{
	return transform.GetRotation();
}

void dae::TransformComponent::SetRotation(const float rotation)
{
	transform.SetRotation(rotation);
}

void dae::TransformComponent::Rotate(const float degrees)
{
	transform.SetRotation(transform.GetRotation() + degrees);
}

