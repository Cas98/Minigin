#include "pch.h"
#include "CameraMovementScript.h"
#include "GameObject.h"
#include "Time.h"
#include "Renderer.h"


CameraMovementScript::CameraMovementScript(float cameraSpeed)
	:m_CameraSpeed(cameraSpeed)
{
	
}

void CameraMovementScript::Init()
{
	m_InputRef = GetParentObject()->GetComponent<dae::InputComponent>();
	m_TransformRef = GetParentObject()->GetComponent<dae::TransformComponent>();

	//map keys for movement
	m_InputRef->MapKey(dae::ControllerButton::NONE, 'W', std::make_shared<MoveCommand>(m_TransformRef, m_CameraSpeed, Direction::UP), dae::KeyState::Down);
	m_InputRef->MapKey(dae::ControllerButton::NONE, 'S', std::make_shared<MoveCommand>(m_TransformRef, m_CameraSpeed, Direction::DOWN), dae::KeyState::Down);
	m_InputRef->MapKey(dae::ControllerButton::NONE, 'A', std::make_shared<MoveCommand>(m_TransformRef, m_CameraSpeed, Direction::LEFT), dae::KeyState::Down);
	m_InputRef->MapKey(dae::ControllerButton::NONE, 'D', std::make_shared<MoveCommand>(m_TransformRef, m_CameraSpeed, Direction::RIGHT), dae::KeyState::Down);

	m_WindowSize = dae::Renderer::GetInstance().GetWindowSize();
}

void CameraMovementScript::Update()
{
	glm::vec2 mousePos = m_InputRef->GetMousePos();

	if(mousePos.x < m_Offset)
	{
		m_TransformRef->Translate(-m_CameraSpeed * dae::Time::GetInstance().GetDeltaTime(), 0.0f, 0.0f);
	}

	if (mousePos.x > m_WindowSize.x - m_Offset)
	{
		m_TransformRef->Translate(m_CameraSpeed * dae::Time::GetInstance().GetDeltaTime(), 0.0f, 0.0f);
	}

	if (mousePos.y < m_Offset)
	{
		m_TransformRef->Translate(0.0f, m_CameraSpeed * dae::Time::GetInstance().GetDeltaTime(), 0.0f);
	}

	if (mousePos.y > m_WindowSize.y - m_Offset)
	{
		m_TransformRef->Translate(0.0f, -m_CameraSpeed * dae::Time::GetInstance().GetDeltaTime(), 0.0f);
	}
}