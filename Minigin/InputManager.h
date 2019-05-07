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
		
		bool Down(ControllerButton button) const;
		bool Pressed(ControllerButton button) const;
		bool Released(ControllerButton button) const;
		bool Up(ControllerButton button) const;
		//void MapKey(ControllerButton button, std::shared_ptr<Command> command, dae::KeyState executeState);
		//void HandleInput();
		KeyState GetKeyState(ControllerButton button) const;
	private:
		bool WasPressed(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		std::vector<KeyInfo> mMappings;

		XINPUT_STATE mState;
		XINPUT_STATE mPrevState;
	};

}
