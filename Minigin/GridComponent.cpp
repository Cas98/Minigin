#include "MiniginPCH.h"
#include "GridComponent.h"
#include "GameObject.h"

dae::GridComponent::GridComponent(int width, int height)
	:BaseComponent(CompType::Grid)
{
	if(width <= 0)
	{
		std::cout << "ERROR: Grid component width 0 or negative set to 1\n";
	}
	else
	{
		m_Width = width;
	}

	if (height <= 0)
	{
		std::cout << "ERROR: Grid component height 0 or negative set to 1\n";
	}
	else
	{
		m_Width = height;
	}


	for(int w(0); w < m_Width; ++w)
	{
		std::vector<GameObject*> objects;
		for (int h(0); h < m_Height; ++h)
		{
			objects.push_back(nullptr);
		}

		m_pGameObjects.push_back(objects);
	}
}

dae::GameObject* dae::GridComponent::GetGameObject(int width, int height)
{
	if(width < 0 || width >= m_Width)
	{
		std::cout << "ERROR: Grid component (GetGameObject) invalid width index\n";
		return nullptr;
	}

	if (height < 0 || height >= m_Height)
	{
		std::cout << "ERROR: Grid component (GetGameObject) invalid height index\n";
		return nullptr;
	}

	return m_pGameObjects[width][height];
}

void dae::GridComponent::SetGameObject(int width, int height, dae::GameObject* pGameObject)
{
	if (width < 0 || width >= m_Width)
	{
		std::cout << "ERROR: Grid component (SetGameObject) invalid width index\n";
		return;
	}

	if (height < 0 || height >= m_Height)
	{
		std::cout << "ERROR: Grid component (SetGameObject) invalid height index\n";
		return;
	}

	if(m_pGameObjects[width][height] != nullptr)
	{
		BaseComponent::GetGameObject()->RemoveChild(m_pGameObjects[width][height]);
	}

	BaseComponent::GetGameObject()->AddChild(pGameObject);
	m_pGameObjects[width][height] = pGameObject;
}

void dae::GridComponent::RemoveGameObject(dae::GameObject* pGameObject)
{
	for (int w{0}; w < m_Width; ++w)
	{
		for (int h{ 0 }; h < m_Height; ++h)
		{
			if(pGameObject == m_pGameObjects[w][h])
			{
				m_pGameObjects[w][h] = nullptr;
				return;
			}
		}
	}
}

void dae::GridComponent::RemoveGameObject(int width, int height)
{
	if (width < 0 || width >= m_Width)
	{
		std::cout << "ERROR: Grid component (RemoveGameObject) invalid width index\n";
		return;
	}

	if (height < 0 || height >= m_Height)
	{
		std::cout << "ERROR: Grid component (RemoveGameObject) invalid height index\n";
		return;
	}

	m_pGameObjects[width][height] = nullptr;
}