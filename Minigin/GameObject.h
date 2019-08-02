#pragma once
#include <memory>
#include "Transform.h"
#include "SceneObject.h"
#include <vector>
#include "Scene.h"
#include "TransformComponent.h"


namespace dae
{
	class BaseComponent;

	class GameObject final 
	{
	public:
		void Update();
		void Render() const;

		void Destroy();

		void AddComponent(BaseComponent* component);
		void RemoveComponent(BaseComponent* component);

		void AddChild(GameObject* gameObject);
		void RemoveChild(GameObject* gameObject);
		GameObject* GetParentObject() const;

		bool HasComponent(BaseComponent* component) const;

		void SetScene(Scene* scene);
		Scene* GetScene();

		TransformComponent* GetTransformComponent() const;

		std::string GetTag() const;
		void SetTag(const std::string& newTag);

		template<typename compType>
		compType* GetComponent();

		GameObject(glm::vec3 pos = { 0.0f,0.0f,0.0f }, float rotation = 0.0f, glm::vec2 scale = { 1.0f,1.0f });
		
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		~GameObject();

		std::vector<BaseComponent*> mComponents;
		std::vector<GameObject*> mChildren;

		GameObject* mpParent = nullptr;
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


