#pragma once
#include <ScriptComponent.h>
#include "helpers.h"
#include <glm/detail/type_vec2.hpp>

class PlayerScript final : public dae::ScriptComponent
{
public:
	PlayerScript(dae::Direction direction, dae::GameObject* pPlayerManager, glm::vec2 spawnCoords);
	~PlayerScript();

	virtual void Init() override;
	virtual void Update() override;

	dae::Direction GetDirection() const;
	void SetDirection(dae::Direction direction);
	void Kill();

	glm::vec2 GetSpawnCoords() const;

private:
	dae::Direction m_Direction;
	dae::GameObject* m_pPlayerManager;
	glm::vec2 m_SpawnCoords;
};

