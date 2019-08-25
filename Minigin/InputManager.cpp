#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>


bool dae::InputManager::ProcessInput()
{
	//get gamepad states
	for (unsigned int i{ 0 };  i < m_GamepadState.size(); ++i)
	{
		m_PrevGamepadState[i] = m_GamepadState[i];
		XInputGetState(i, &m_GamepadState[i]);

		if (m_GamepadState[i].Gamepad.wButtons == 52428 || m_GamepadState[i].Gamepad.wButtons == 32764 
			|| m_GamepadState[i].Gamepad.wButtons == 6333 || m_GamepadState[i].Gamepad.wButtons == 29793)
		{
			m_GamepadState[i].Gamepad.wButtons = 0;
		}
	}

	//get keyboard states
	if (m_KeyboardState0Active)
	{
		GetKeyboardState(m_pKeyboardState1);
		m_pPrevKeyboardState = m_pKeyboardState0;
		m_pKeyboardState = m_pKeyboardState1;
	}
	else
	{
		GetKeyboardState(m_pKeyboardState0);
		m_pPrevKeyboardState = m_pKeyboardState1;
		m_pKeyboardState = m_pKeyboardState0;
	}
	m_KeyboardState0Active = !m_KeyboardState0Active;

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	HandleInput();

	return true;
}

void dae::InputManager::Destroy()
{
	delete m_pKeyboardState;
	delete m_pPrevKeyboardState;
}

void dae::InputManager::Init()
{
	m_pKeyboardState0 = new BYTE[256];
	m_pKeyboardState1 = new BYTE[256];

	GetKeyboardState(m_pKeyboardState0);
	GetKeyboardState(m_pKeyboardState1);

	for (int i{ 0 }; i < m_MaxUsers; ++i)
	{
		XINPUT_STATE state;
		XINPUT_STATE prevstate;
		m_GamepadState.push_back(state);
		m_PrevGamepadState.push_back(prevstate);
	}
}

void dae::InputManager::HandleInput()
{

}

//gamepad
dae::KeyState dae::InputManager::GetGamepadKeyState(ControllerButton button, const  int playerIndex) const
{
	if (WasGamepadPressed(button, playerIndex))
	{
		if (IsGamepadPressed(button, playerIndex))
		{
			return dae::KeyState::Down;
		}
		else
		{
			return dae::KeyState::Released;
		}
	}
	if (IsGamepadPressed(button, playerIndex))
	{
		return dae::KeyState::Pressed;
	}
	else
	{
		return dae::KeyState::Up;
	}
}

bool dae::InputManager::IsGamepadPressed(ControllerButton button, const int playerIndex) const
{
	return (m_GamepadState[playerIndex].Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::WasGamepadPressed(ControllerButton button, const int playerIndex) const
{
	return (m_PrevGamepadState[playerIndex].Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::GamepadReleased(ControllerButton button, const int playerIndex) const
{
	if (GetGamepadKeyState(button, playerIndex) == dae::KeyState::Released) return true;
	return false;
}

bool dae::InputManager::GamepadUp(ControllerButton button, const int playerIndex) const
{
	if (GetGamepadKeyState(button, playerIndex) == dae::KeyState::Up) return true;
	return false;
}

bool dae::InputManager::GamepadDown(ControllerButton button, const int playerIndex) const
{
	if (GetGamepadKeyState(button, playerIndex) == dae::KeyState::Down) return true;
	return false;
}

bool dae::InputManager::GamepadPressed(ControllerButton button, const int playerIndex) const
{
	if (GetGamepadKeyState(button, playerIndex) == dae::KeyState::Pressed) return true;
	return false;
}

//keyboard
dae::KeyState dae::InputManager::GetKeyboardKeyState(int key) const
{
	if (WasKeyboardPressed(key))
	{
		if (IsKeyboardPressed(key))
		{
			return dae::KeyState::Down;
		}
		else
		{
			return dae::KeyState::Released;
		}
	}
	if (IsKeyboardPressed(key))
	{
		return dae::KeyState::Pressed;
	}
	else
	{
		return dae::KeyState::Up;
	}
}

bool dae::InputManager::IsKeyboardPressed(int key) const
{
	if (m_pKeyboardState == nullptr) return false;
	return (m_pKeyboardState[key] & 0xF0) != 0;
}

bool dae::InputManager::WasKeyboardPressed(int key) const
{
	if (m_pPrevKeyboardState == nullptr) return false;
	return (m_pPrevKeyboardState[key] & 0xF0) != 0;
}

bool dae::InputManager::KeyboardReleased(int key) const
{
	if (GetKeyboardKeyState(key) == dae::KeyState::Released) return true;
	return false;
}

bool dae::InputManager::KeyboardUp(int key) const
{
	if (GetKeyboardKeyState(key) == dae::KeyState::Up) return true;
	return false;
}

bool dae::InputManager::KeyboardDown(int key) const
{
	if (GetKeyboardKeyState(key) == dae::KeyState::Down) return true;
	return false;
}

bool dae::InputManager::KeyboardPressed(int key) const
{
	if (GetKeyboardKeyState(key) == dae::KeyState::Pressed) return true;
	return false;
}

glm::vec2 dae::InputManager::GetMousePos() const
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	return(glm::vec2(x,y));
}