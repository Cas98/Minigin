#pragma once
#include "SceneManager.h"
#include "CameraComponent.h"

namespace dae
{
	class SceneObject;
	class CameraComponent;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();
		void Render() const;

		std::string GetName();

		CameraComponent* GetActiveCamera() const;
		void SetActiveCamera(CameraComponent* pActiveCamera);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};
		CameraComponent* m_pActiveCamera = nullptr;

		static unsigned int idCounter; 
	};

}
