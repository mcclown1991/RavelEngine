#pragma once

#include <map>

#include "RawInput.h"


class InputBinding {
	// attributes
public:
	enum class Type : byte {
		KEY_OR_MOUSE_BUTTON = 1 << 1,
		MOUSE_MOVEMENT,
		JOYSTICK_AXIS
	};
	
	std::string name;
	std::string description;
	WORD negative;
	WORD positive;
	WORD alt_negative;
	WORD alt_positive;
	bool invert;
	Type type;
};

class Input {
public:
	Input();
	~Input();

	void InitializeInput(HWND hWnd);
	static float GetAxis(std::string_view axisName);
	static float GetRawAxis(std::string_view axisName);
	static bool GetButton(std::string_view buttonName);

private:
	static XBOXController* controller;
	static std::map<std::string, InputBinding*> keyboard;

	std::map<std::string, WORD> stringToKeyDefines;
};

Input* GetInput();