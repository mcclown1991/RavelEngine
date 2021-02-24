#pragma once

#include <map>

#include "RawInput.h"

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
	static std::map<std::string, std::pair<WORD, WORD>> keyboard;
};

Input* GetInput();