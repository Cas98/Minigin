#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "Scene.h"

namespace dae
{
	class CameraComponent final : public dae::BaseComponent
	{
	public:
		CameraComponent(bool setActive = false);
		virtual ~CameraComponent() = default;

		virtual void Init();

		void SetActive();
		void SetInActive();
		bool IsActive();

		TransformComponent* GetTransform() const;

	private:
		dae::TransformComponent* m_pTransformRef = nullptr;
		Scene* m_pSceneRef = nullptr;
		bool m_IsActive = false;
	};
}

