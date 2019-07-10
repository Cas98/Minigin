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
		void AddScene(std::shared_ptr<dae::Scene> scene);
		void RemoveScene(const std::string& name);

		void SetActiveScene(const std::string& name);
		std::shared_ptr<Scene> GetActiveScene();

		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> mpActiveScene;
	};

}
