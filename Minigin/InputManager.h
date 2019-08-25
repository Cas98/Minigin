#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>


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

		//mouse
		glm::vec2 GetMousePos() const;

		void HandleInput();

	private:
		//gamepad
		bool WasGamepadPressed(ControllerButton button, const  int playerIndex) const;
		bool IsGamepadPressed(ControllerButton button, const  int playerIndex) const;

		//keyboard
		bool WasKeyboardPressed(int keyboardCode) const;
		bool IsKeyboardPressed(int keyboardCode) const;

		const int m_MaxUsers = 4;
		std::vector <XINPUT_STATE> m_GamepadState;
		std::vector <XINPUT_STATE> m_PrevGamepadState;
		BYTE *m_pKeyboardState, *m_pPrevKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		bool m_KeyboardState0Active = true;
	};

}
