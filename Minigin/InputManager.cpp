#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	mPrevState = mState;
	XInputGetState(0, &mState);

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

dae::KeyState dae::InputManager::GetKeyState(ControllerButton button) const
{
	if (WasPressed(button))
	{
		if (IsPressed(button))
		{
			return dae::KeyState::Down;
		}
		else
		{
			return dae::KeyState::Released;
		}
	}
	if (IsPressed(button))
	{
		return dae::KeyState::Pressed;
	}
	else
	{
		return dae::KeyState::Up;
	}
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return (mState.Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::WasPressed(ControllerButton button) const
{
	return (mPrevState.Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::Released(ControllerButton button) const
{
	if (GetKeyState(button) == dae::KeyState::Released) return true;
	return false;
}

bool dae::InputManager::Up(ControllerButton button) const
{
	if (GetKeyState(button) == dae::KeyState::Up) return true;
	return false;
}

bool dae::InputManager::Down(ControllerButton button) const
{
	if (GetKeyState(button) == dae::KeyState::Down) return true;
	return false;
}

bool dae::InputManager::Pressed(ControllerButton button) const
{
	if (GetKeyState(button) == dae::KeyState::Pressed) return true;
	return false;
}

//void dae::InputManager::HandleInput()
//{
//	for (size_t i{ 0 }; i < mMappings.size(); ++i)
//	{
//		if (GetKeyState(mMappings[i].button) == mMappings[i].executeState) mMappings[i].command->Execute();
//	}
//}
