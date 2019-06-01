#include "MiniginPCH.h"
#include "Transform.h"

//transform
void dae::Transform::SetTransform(const glm::vec3& pos, const glm::vec2& scale, const float rotation)
{
	m_Position = pos;
	m_Scale = scale;
	m_Rotation = rotation;
}

//pos
void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

//scale
void dae::Transform::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void dae::Transform::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
}

//rot
void dae::Transform::SetRotation(const float rotation)
{
	m_Rotation = rotation;
}