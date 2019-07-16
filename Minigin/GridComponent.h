#pragma once
#include "BaseComponent.h"

//add observer pattern with gameobject to notify when object i destroyed to remove from grid
//add removegameobject function

namespace dae
{
	class GridComponent final: public BaseComponent
	{
	public:
		GridComponent(int width, int height);
		~GridComponent() = default;

		GameObject* GetGameObject(int width, int height);
		void SetGameObject(int width, int height, GameObject* pGameObject);
		void RemoveGameObject(GameObject* pGameObject);
		void RemoveGameObject(int width, int height);

	private:
		std::vector<std::vector<GameObject*>> m_pGameObjects;
		int m_Width = 1;
		int m_Height = 1;
		float m_Offset = 0.0f;
	};
}

