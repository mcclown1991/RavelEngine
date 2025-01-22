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

	void BindAxis(std::string_view axis, size_t instance, std::function<void(float)> const& function);
	void BlindAction(std::string_view action, size_t instance, std::function<void()> const& function);

	void UnbindAxis(std::string_view axis, size_t instance);
	void UnBindAction(std::string_view action, size_t instance);

private:
	static XBOXController* controller;

	std::map<std::string, std::vector<std::pair<Keystroke, float>>> axisMapping;
	std::map<std::string, std::vector<Keystroke>> actionMapping;

	std::map<size_t, std::vector<std::pair<std::string, std::function<void(float)>>>> axisFunction;
	std::map<size_t, std::vector<std::pair<std::string, std::function<void()>>>> actionFunction;

	std::map<std::string, WORD> stringToKeyDefines;
};

Input* GetInput();