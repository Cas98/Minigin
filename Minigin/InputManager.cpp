#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>


bool dae::InputManager::ProcessInput()
{
	//gamepad
	for (int i{ 0 };  i < mGamepadState.size(); ++i)
	{
		mPrevGamepadState[i] = mGamepadState[i];
		XInputGetState(i, &mGamepadState[i]);
	}

	//keyboard
	if (mKeyboardState0Active)
	{
		GetKeyboardState(mpKeyboardState1);
		mpPrevKeyboardState = mpKeyboardState0;
		mpKeyboardState = mpKeyboardState1;
	}
	else
	{
		GetKeyboardState(mpKeyboardState0);
		mpPrevKeyboardState = mpKeyboardState1;
		mpKeyboardState = mpKeyboardState0;
	}
	mKeyboardState0Active = !mKeyboardState0Active;

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
	delete mpKeyboardState;
	delete mpPrevKeyboardState;
}

void dae::InputManager::Init()
{
	mpKeyboardState0 = new BYTE[256];
	mpKeyboardState1 = new BYTE[256];

	GetKeyboardState(mpKeyboardState0);
	GetKeyboardState(mpKeyboardState1);

	for (int i{ 0 }; i < m_MaxUsers; ++i)
	{
		XINPUT_STATE state;
		XINPUT_STATE prevstate;
		mGamepadState.push_back(state);
		mPrevGamepadState.push_back(prevstate);
	}
}

void dae::InputManager::MapKey(ControllerButton button, int keyboard, std::shared_ptr<Command> command, dae::KeyState executeState, int userIndex)
{
	KeyInfo keyInfo;
	keyInfo.button = button;
	keyInfo.keyboard = keyboard;
	keyInfo.command = command;
	keyInfo.executeState = executeState;
	keyInfo.userIndex = userIndex;

	mMappings.push_back(keyInfo);
}

void dae::InputManager::HandleInput()
{
	for (size_t i{ 0 }; i < mMappings.size(); ++i)
	{
		if (GetGamepadKeyState(mMappings[i].button, mMappings[i].userIndex) == mMappings[i].executeState
			|| GetKeyboardKeyState(mMappings[i].keyboard) == mMappings[i].executeState) mMappings[i].command->Execute();
	}
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
	return (mGamepadState[playerIndex].Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::WasGamepadPressed(ControllerButton button, const int playerIndex) const
{
	return (mPrevGamepadState[playerIndex].Gamepad.wButtons & WORD(button)) != 0;
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
	if (mpKeyboardState == nullptr) return false;
	return (mpKeyboardState[key] & 0xF0) != 0;
}

bool dae::InputManager::WasKeyboardPressed(int key) const
{
	if (mpPrevKeyboardState == nullptr) return false;
	return (mpPrevKeyboardState[key] & 0xF0) != 0;
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