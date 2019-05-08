#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const glm::vec3& pos = glm::vec3(0.0f,0.0f,0.0f));
		~TransformComponent() = default;

		const glm::vec3& GetPosition() const;
		void SetPosition(const float x, const  float y, const  float z);
	
	private:
		Transform transform;
	};
}

