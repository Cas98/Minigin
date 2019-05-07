#pragma once
#include <memory>
#include "Transform.h"
#include "SceneObject.h"
#include <vector>

//test



namespace dae
{
	class BaseComponent;

	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void AddComponent(BaseComponent* component);

		template<typename compType>
		compType* GetComponent();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> mComponents;
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
