#pragma once
#include <Scene.h>
class PauseMenu final: public dae::Scene
{
public:
	PauseMenu();
	~PauseMenu();

	void SetCurrentLevel(const std::string& levelName);

private:
	virtual void Initialize() override;
	virtual void Update() override;

	std::string m_CurrentLevelName;
};

