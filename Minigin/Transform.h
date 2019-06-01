#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		glm::vec3 m_Position;
		glm::vec2 m_Scale;
		float m_Rotation;

	public:
		//transform
		void SetTransform(const glm::vec3& pos, const glm::vec2& scale, const float rotation);

		//pos
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);

		//scale
		const glm::vec2& GetScale() const { return m_Scale; }
		void SetScale(float x, float y);
		void SetScale(const glm::vec2& scale);

		//rot
		const float GetRotation() const { return m_Rotation; }
		void SetRotation(const float rotation);
	};
}
