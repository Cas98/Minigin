#pragma once
#include <ScriptComponent.h>
#include "Observer.h"

class ScoreScript final: public dae::ScriptComponent , public Observer
{
public:
	ScoreScript();
	~ScoreScript();

	virtual void Init() override;
	virtual void Update() override;

	void OnNotify(dae::GameObject* gameObject, const std::string& message) override;

private:
	int m_Score = 0;

	void AddScore(int score);
};

