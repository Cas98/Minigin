#pragma once
#include <ScriptComponent.h>
#include "InputComponent.h"
#include "TransformComponent.h"
#include "Time.h"

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class CameraMovementScript final: public dae::ScriptComponent
{
public:
	CameraMovementScript(float cameraSpeed = 200.0f);
	virtual void Init() override;
	virtual void Update() override;

private:
	dae::InputComponent* m_InputRef = nullptr;
	dae::TransformComponent* m_TransformRef = nullptr;
	float m_CameraSpeed;
	glm::vec2 m_WindowSize;
	float m_Offset = 40.0f;
};

//move commands
class MoveCommand : public dae::Command
{
public:
	MoveCommand(dae::TransformComponent* transformRef, float speed, Direction dir)
		:m_TransformRef(transformRef), m_Speed(speed), m_Direction(dir)
	{
		
	};

	void Execute() override
	{
		switch(m_Direction)
		{
		case Direction::UP:
			m_TransformRef->Translate(0.0f, m_Speed * dae::Time::GetInstance().GetDeltaTime(), 0.0f);
			break;

		case Direction::DOWN:
			m_TransformRef->Translate(0.0f, -m_Speed * dae::Time::GetInstance().GetDeltaTime(), 0.0f);
			break;

		case Direction::LEFT:
			m_TransformRef->Translate(-m_Speed * dae::Time::GetInstance().GetDeltaTime(), 0.0f, 0.0f);
			break;

		case Direction::RIGHT:
			m_TransformRef->Translate(m_Speed * dae::Time::GetInstance().GetDeltaTime(), 0.0f, 0.0f);
			break;
		}
	}

private:
	float m_Speed;
	dae::TransformComponent* m_TransformRef = nullptr;
	Direction m_Direction;
};