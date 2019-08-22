#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

namespace dae
{
	struct KeyInfo
	{
		ControllerButton button;
		int keyboard;
		KeyState executeState;
		Command* pCommand;
	};

	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent(int playerIndex);
		~InputComponent() override;

		void Update() override;

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

		void MapKey(ControllerButton button, int keyboard, Command* command, KeyState executeState);

		//mouse
		glm::vec2 GetMousePos() const;

		int GetPlayerIndex() const;

	private:
		int m_PlayerIndex;

		std::vector<KeyInfo> m_Mappings;
	};
}

