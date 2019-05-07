#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	//gamepad
	mPrevGamepadState = mGamepadState;
	XInputGetState(0, &mGamepadState);

	//keyboard
	mPrevKeyboardState = mKeyboardState;
	GetKeyboardState(&mKeyboardState);

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

	return true;
}

//void dae::InputManager::MapKey(ControllerButton button, std::shared_ptr<Command> command, dae::KeyState executeState)
//{
//	KeyInfo keyInfo;
//	keyInfo.button = button;
//	keyInfo.command = command;
//	keyInfo.executeState = executeState;
//
//	mMappings.push_back(keyInfo);
//}

//void dae::InputManager::HandleInput()
//{
//	for (size_t i{ 0 }; i < mMappings.size(); ++i)
//	{
//		if (GetKeyState(mMappings[i].button) == mMappings[i].executeState) mMappings[i].command->Execute();
//	}
//}


dae::KeyState dae::InputManager::GetGamepadKeyState(ControllerButton button) const
{
	if (WasGamepadPressed(button))
	{
		if (IsGamepadPressed(button))
		{
			return dae::KeyState::Down;
		}
		else
		{
			return dae::KeyState::Released;
		}
	}
	if (IsGamepadPressed(button))
	{
		return dae::KeyState::Pressed;
	}
	else
	{
		return dae::KeyState::Up;
	}
}

bool dae::InputManager::IsGamepadPressed(ControllerButton button) const
{
	return (mGamepadState.Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::WasGamepadPressed(ControllerButton button) const
{
	return (mPrevGamepadState.Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::GamepadReleased(ControllerButton button) const
{
	if (GetGamepadKeyState(button) == dae::KeyState::Released) return true;
	return false;
}

bool dae::InputManager::GamepadUp(ControllerButton button) const
{
	if (GetGamepadKeyState(button) == dae::KeyState::Up) return true;
	return false;
}

bool dae::InputManager::GamepadDown(ControllerButton button) const
{
	if (GetGamepadKeyState(button) == dae::KeyState::Down) return true;
	return false;
}

bool dae::InputManager::GamepadPressed(ControllerButton button) const
{
	if (GetGamepadKeyState(button) == dae::KeyState::Pressed) return true;
	return false;
}

