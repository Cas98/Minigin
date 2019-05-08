#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LefthThumb = 0x0040,
		RightThumb = 0x0080,
		LefthShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
	};

	enum class KeyState
	{
		Pressed,
		Down,
		Released,
		Up
	};

	struct KeyInfo
	{
		ControllerButton button;
		KeyState executeState;
		//std::shared_ptr<Command> command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void Init();
		void Destroy();
		
		//gamepad
		bool GamepadDown(ControllerButton button) const;
		bool GamepadPressed(ControllerButton button) const;
		bool GamepadReleased(ControllerButton button) const;
		bool GamepadUp(ControllerButton button) const;
		KeyState GetGamepadKeyState(ControllerButton button) const;

		//keyboard
		bool KeyboardDown(int keyboardCode) const;
		bool KeyboardPressed(int keyboardCode) const;
		bool KeyboardReleased(int keyboardCode) const;
		bool KeyboardUp(int keyboardCode) const;
		KeyState GetKeyboardKeyState(int keyboardCode) const;

		//void MapKey(ControllerButton button, std::shared_ptr<Command> command, dae::KeyState executeState);
		//void HandleInput();
		
	private:
		//gamepad
		bool WasGamepadPressed(ControllerButton button) const;
		bool IsGamepadPressed(ControllerButton button) const;

		//keyboard
		bool WasKeyboardPressed(int keyboardCode) const;
		bool IsKeyboardPressed(int keyboardCode) const;

		std::vector<KeyInfo> mMappings;

		XINPUT_STATE mGamepadState;
		XINPUT_STATE mPrevGamepadState;
		BYTE *mpKeyboardState, *mpPrevKeyboardState, *mpKeyboardState0, *mpKeyboardState1;
		bool mKeyboardState0Active = true;
	};

}
