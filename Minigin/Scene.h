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
		void Remove(GameObject* object);

		std::string GetName();

		~Scene();
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
		void RootRender() const;

		std::string mName{};
		std::vector <GameObject*> mObjects{};

		static unsigned int idCounter; 
	};

}
