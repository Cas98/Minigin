#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* scene);
		void RemoveScene(const std::string& name);

		void SetActiveScene(const std::string& name);
		Scene* GetActiveScene();

		void Update();
		void Destroy();

	private:
		std::vector<Scene*> mScenes;
		Scene* mpActiveScene;
	};

}
