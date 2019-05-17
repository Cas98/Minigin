#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>

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
		ButtonY = 0x8000,
		NONE = 0x0000
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
		int keyboard;
		KeyState executeState;
		std::shared_ptr<Command> command;
		int userIndex;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void Init();
		void Destroy();
		
		//gamepad
		bool GamepadDown(ControllerButton button, const  int playerIndex) const;
		bool GamepadPressed(ControllerButton button, const  int playerIndex) const;
		bool GamepadReleased(ControllerButton button, const  int playerIndex) const;
		bool GamepadUp(ControllerButton button, const  int playerIndex) const;
		KeyState GetGamepadKeyState(ControllerButton button, const  int playerIndex) const;

		//keyboard
		bool KeyboardDown(int keyboardCode) const;
		bool KeyboardPressed(int keyboardCode) const;
		bool KeyboardReleased(int keyboardCode) const;
		bool KeyboardUp(int keyboardCode) const;
		KeyState GetKeyboardKeyState(int keyboardCode) const;

		void MapKey(ControllerButton button, int keyboard, std::shared_ptr<Command> command, dae::KeyState executeState, int userIndex);
		void HandleInput();

	private:
		//gamepad
		bool WasGamepadPressed(ControllerButton button, const  int playerIndex) const;
		bool IsGamepadPressed(ControllerButton button, const  int playerIndex) const;

		//keyboard
		bool WasKeyboardPressed(int keyboardCode) const;
		bool IsKeyboardPressed(int keyboardCode) const;

		std::vector<KeyInfo> mMappings;

		const int m_MaxUsers = 4;
		std::vector <XINPUT_STATE> mGamepadState;
		std::vector <XINPUT_STATE> mPrevGamepadState;
		BYTE *mpKeyboardState, *mpPrevKeyboardState, *mpKeyboardState0, *mpKeyboardState1;
		bool mKeyboardState0Active = true;
	};

}
