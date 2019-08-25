#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class GridComponent final: public BaseComponent
	{
	public:
		GridComponent(int width, int height, float offset);
		~GridComponent() override = default;

		//Get gameobject at specific coordinates
		GameObject* GetGameObject(int width, int height);
		//Set gameobject at specific coordinates
		void SetGameObject(int width, int height, GameObject* pGameObject, bool updatePos = true);
		//Remave gameobject from grid
		void RemoveGameObject(GameObject* pGameObject);
		//Remove gameobject at specific coordinates
		void RemoveGameObject(int width, int height);

		int GetWidth() const;
		int GetHeight() const;
		float GetOffset() const;

		//Get coordinates on grid from gameobject
		glm::vec2 GetGameObjectPos(GameObject* pGameObject);
		//Manually set correct position on grid for gameobject
		void UpdatePos(GameObject* pGameObject);

	private:
		//gameobjects on grid
		std::vector<std::vector<GameObject*>> m_pGameObjects;
		int m_Width = 1;
		int m_Height = 1;
		float m_Offset;
	};
}

