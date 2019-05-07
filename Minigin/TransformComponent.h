#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const glm::vec3& pos = glm::vec3(0.0f,0.0f,0.0f));
		~TransformComponent() = default;

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
	
	private:
		glm::vec3 mPosition;
	};
}

