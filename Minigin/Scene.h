#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const std::string& name);
		void Add(GameObject* object);
		void AddThreaded(GameObject* object);
		void Remove(GameObject* object);

		std::string GetName();

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		virtual void Initialize() = 0;
		virtual void Update() = 0;

	private:
		friend SceneManager;

		void RootInitialize();
		void RootUpdate();
		void DeleteObjects();
		void AddObjects();

		std::string mName{};
		std::vector <GameObject*> m_pObjects{};
		std::vector <GameObject*> m_pAddedObjects{};
		std::vector <GameObject*> m_pObjectsToDelete{};
		std::vector <GameObject*> m_pObjectsThread{};
		std::vector <GameObject*> m_pAddedObjectsThread{};

		static unsigned int m_IdCounter;

		bool m_IsInizialized = false;
	};

}
