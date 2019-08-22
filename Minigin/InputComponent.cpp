#include "MiniginPCH.h"
#include "InputComponent.h"

dae::InputComponent::InputComponent(int playerIndex)
	:BaseComponent(dae::CompType::Input)
{
	if(playerIndex >= 0)
	{
		m_PlayerIndex = playerIndex;
	}
	else
	{
		m_PlayerIndex = 0;
	}
}

dae::InputComponent::~InputComponent()
{
	for (size_t i{ 0 }; i < m_Mappings.size(); ++i)
	{
		delete m_Mappings[i].pCommand;
	}
}

void dae::InputComponent::Update()
{
	for (size_t i{ 0 }; i < m_Mappings.size(); ++i)
	{
		if (GetGamepadKeyState(m_Mappings[i].button) == m_Mappings[i].executeState
			|| GetKeyboardKeyState(m_Mappings[i].keyboard) == m_Mappings[i].executeState) m_Mappings[i].pCommand->Execute();
	}
}

//gamepad
bool dae::InputComponent::GamepadDown(dae::ControllerButton button) const
{
	return dae::InputManager::GetInstance().GamepadDown(button, m_PlayerIndex);
}

bool dae::InputComponent::GamepadPressed(dae::ControllerButton button) const
{
	return dae::InputManager::GetInstance().GamepadPressed(button, m_PlayerIndex);
}

bool dae::InputComponent::GamepadReleased(dae::ControllerButton button) const
{
	return dae::InputManager::GetInstance().GamepadReleased(button, m_PlayerIndex);
}

bool dae::InputComponent::GamepadUp(dae::ControllerButton button) const
{
	return dae::InputManager::GetInstance().GamepadUp(button, m_PlayerIndex);
}

dae::KeyState dae::InputComponent::GetGamepadKeyState(dae::ControllerButton button) const
{
	return dae::InputManager::GetInstance().GetGamepadKeyState(button, m_PlayerIndex);
}

//keyboard
bool dae::InputComponent::KeyboardDown(int keyboardCode) const
{
	return dae::InputManager::GetInstance().KeyboardDown(keyboardCode);
}

bool dae::InputComponent::KeyboardPressed(int keyboardCode) const
{
	return dae::InputManager::GetInstance().KeyboardPressed(keyboardCode);
}

bool dae::InputComponent::KeyboardReleased(int keyboardCode) const
{
	return dae::InputManager::GetInstance().KeyboardReleased(keyboardCode);
}

bool dae::InputComponent::KeyboardUp(int keyboardCode) const
{
	return dae::InputManager::GetInstance().KeyboardUp(keyboardCode);
}

dae::KeyState dae::InputComponent::GetKeyboardKeyState(int keyboardCode) const
{
	return dae::InputManager::GetInstance().GetKeyboardKeyState(keyboardCode);
}

void dae::InputComponent::MapKey(dae::ControllerButton button, int keyboard, Command* command, dae::KeyState executeState)
{
	KeyInfo keyInfo;
	keyInfo.button = button;
	keyInfo.keyboard = keyboard;
	keyInfo.pCommand = command;
	keyInfo.executeState = executeState;

	m_Mappings.push_back(keyInfo);
}

glm::vec2 dae::InputComponent::GetMousePos() const
{
	return(dae::InputManager::GetInstance().GetMousePos());
}

int dae::InputComponent::GetPlayerIndex() const
{
	return m_PlayerIndex;
}