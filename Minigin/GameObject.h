#pragma once
#include "Transform.h"
#include <vector>
#include "Scene.h"
#include "TransformComponent.h"

namespace dae
{
	class BaseComponent;

	class GameObject final 
	{
	public:
		GameObject(glm::vec3 pos = { 0.0f,0.0f,1.0f }, float rotation = 0.0f, glm::vec2 scale = { 1.0f,1.0f });

		void Destroy();

		void Update();

		//components
		void AddComponent(BaseComponent* component);
		void RemoveComponent(BaseComponent* component);
		bool HasComponent(BaseComponent* component) const;

		template<typename compType>
		compType* GetComponent();

		//scene
		Scene* GetScene();

		//transform
		TransformComponent* GetTransformComponent() const;

		//tags
		std::string GetTag() const;
		void SetTag(const std::string& newTag);

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		friend Scene;

		//destructor is private call destroy function instead
		~GameObject();

		//components
		std::vector<BaseComponent*> mComponents;

		//scene
		void SetScene(Scene* scene);
		Scene* m_pScene = nullptr;

		TransformComponent* m_pTransform = nullptr;

		bool m_IsInit = false;

		std::string m_Tag = "Object";
	};
}


template<typename compType>
compType* dae::GameObject::GetComponent()
{
	for (size_t i{ 0 }; i < mComponents.size(); ++i)
	{
		if (typeid(*mComponents[i]) == typeid(compType))
		{
			return dynamic_cast<compType*>(mComponents[i]);
		}
	}

	return nullptr;
}


