#pragma once
#include <ScriptComponent.h>
#include "helpers.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>
#pragma warning(pop)

class PlayerScript final : public dae::ScriptComponent
{
public:
	PlayerScript(Direction direction, dae::GameObject* pPlayerManager, glm::vec2 spawnCoords);
	~PlayerScript();

	virtual void Init() override;
	virtual void Update() override;

	Direction GetDirection() const;
	void SetDirection(Direction direction);
	void Kill();

	glm::vec2 GetSpawnCoords() const;

private:
	Direction m_Direction;
	dae::GameObject* m_pPlayerManager;
	glm::vec2 m_SpawnCoords;
};

