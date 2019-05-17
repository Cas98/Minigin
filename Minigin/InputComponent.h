#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

namespace dae
{
	class InputComponent : public BaseComponent
	{
	public:
		InputComponent(int playerIndex);
		~InputComponent() = default;

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

		void MapKey(ControllerButton button, int keyboard, std::shared_ptr<Command> command, KeyState executeState);

	private:
		int m_PlayerIndex;
	};
}

