#include "pch.h"
#include "TestScript.h"
#include "GameObject.h"
#include "Time.h"

void TestScript::Init()
{
	m_InputRef = GetParentObject()->GetComponent<dae::InputComponent>();
	m_TransformRef = GetParentObject()->GetComponent<dae::TransformComponent>();
}

void TestScript::Update()
{
	if (m_InputRef->KeyboardDown('D'))
	{
		m_TransformRef->Translate(100.0f * dae::Time::GetInstance().GetDeltaTime(), 0.0f, 0.0f);
	}
	if(m_InputRef->KeyboardDown('A'))
	{
		m_TransformRef->Translate(-100.0f * dae::Time::GetInstance().GetDeltaTime(), 0.0f, 0.0f);
	}
	if (m_InputRef->KeyboardDown('S'))
	{
		m_TransformRef->Translate(0.0f, -100.0f * dae::Time::GetInstance().GetDeltaTime(), 0.0f);
	}
	if (m_InputRef->KeyboardDown('W'))
	{
		m_TransformRef->Translate(0.0f, 100.0f * dae::Time::GetInstance().GetDeltaTime(), 0.0f);
	}
	if (m_InputRef->KeyboardDown('Q'))
	{
		m_TransformRef->Rotate(-60.0f * dae::Time::GetInstance().GetDeltaTime());
	}
	if (m_InputRef->KeyboardDown('E'))
	{
		m_TransformRef->Rotate(60.0f * dae::Time::GetInstance().GetDeltaTime());
	}
}