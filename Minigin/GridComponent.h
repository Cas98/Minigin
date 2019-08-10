#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)


//add observer pattern with gameobject to notify when object i destroyed to remove from grid
//add removegameobject function

namespace dae
{
	class GridComponent final: public BaseComponent
	{
	public:
		GridComponent(int width, int height, float offset);
		~GridComponent() = default;

		GameObject* GetGameObject(int width, int height);
		void SetGameObject(int width, int height, GameObject* pGameObject, bool updatePos = true);
		void RemoveGameObject(GameObject* pGameObject);
		void RemoveGameObject(int width, int height);

		int GetWidth() const;
		int GetHeight() const;
		float GetOffset() const;

		glm::vec2 GetGameObjectPos(GameObject* pGameObject);
		void UpdatePos(GameObject* pGameObject);

	private:
		std::vector<std::vector<GameObject*>> m_pGameObjects;
		int m_Width = 1;
		int m_Height = 1;
		float m_Offset;
	};
}

