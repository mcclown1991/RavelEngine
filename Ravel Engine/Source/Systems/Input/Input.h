#pragma once

#include <map>
#include <vector>

#include "RawInput.h"

class Input {
public:
	Input();
	~Input();

	void InitializeInput(HWND hWnd);
	void Update();

	void BindAxis(std::string_view axis, std::function<void(float)> const& function);
	void BlindAction(std::string_view action, std::function<void()> const& function);

private:
	static XBOXController* controller;

	std::map<std::string, std::vector<std::pair<Keystroke, float>>> axisMapping;
	std::map<std::string, std::vector<std::pair<Keystroke, std::bitset<4>>>> actionMapping;

	std::vector<std::pair<std::string, std::function<void(float)>>> axisFunction;

	std::map<std::string, WORD> stringToKeyDefines;
};

Input* GetInput();