#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float rotation = 0.0f, const float scaleX = 1.0f, const float scaleY = 1.0f);
		TransformComponent(const glm::vec3& pos = { 0.0f,0.0f,0.0f }, const float rotation = 0.0f, const glm::vec2& scale = {0.0f,0.0f});
		~TransformComponent() = default;

		//pos
		const glm::vec3 GetPosition() const;
		const glm::vec3 GetWorldPosition() const;
		void SetPosition(const float x, const  float y, const  float z);
		void SetPosition(const glm::vec3& pos);
		void Translate(const float x, const  float y, const  float z = 0.0f);
		void Translate(const glm::vec3& pos);

		//scale
		const glm::vec2 GetScale() const;
		const glm::vec2 GetWorldScale() const;
		void SetScale(const float x, const  float y);
		void SetScale(const glm::vec2& scale);

		//rotate
		const float GetRotation() const;
		const float GetWorldRotation() const;
		void SetRotation(const float rotation);
		void Rotate(const float degrees);
	
	private:
		Transform transform;
	};
}

