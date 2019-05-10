#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const float x = 0.0f, const  float y = 0.0f, const  float z = 0.0f);
		~TransformComponent() = default;

		const glm::vec3& GetPosition() const;
		void SetPosition(const float x, const  float y, const  float z);
	
	private:
		Transform transform;
	};
}

