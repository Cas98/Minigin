#pragma once
#include <ScriptComponent.h>
#include "Observer.h"

class ScoreScript final: public dae::ScriptComponent
{
public:
	ScoreScript();
	~ScoreScript();

private:
	int m_Score = 0;
};

