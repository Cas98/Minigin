#pragma once
#include <ScriptComponent.h>
#include "Observer.h"
#include "TextComponent.h"

class ScoreScript final: public dae::ScriptComponent , public dae::Observer
{
public:
	ScoreScript();
	~ScoreScript();

	virtual void Init() override;
	virtual void Update() override;

	void OnNotify(dae::GameObject* gameObject, const std::string& message) override;
	void AddScore(int score);
	int GetScore() const;

private:
	int m_Score = 0;
	dae::TextComponent* m_pTextCompRef;
	bool m_NeedsUpdate = false;
};

