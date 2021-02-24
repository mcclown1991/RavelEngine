#include "Input.h"
#include "MemoryManager.h"

XBOXController* Input::controller = nullptr;
std::map<std::string, std::pair<WORD, WORD>> Input::keyboard = std::map<std::string, std::pair<WORD, WORD>>({
	{"Horizontal", std::pair(RK_LEFT, RK_RIGHT)},
	{"Vertical", std::pair(RK_UP, RK_DOWN)}
	});

Input* GetInput() {
	static Input s;
	return(&s);
}

Input::Input() {}
Input::~Input() {
	controller->~XBOXController();
}

void Input::InitializeInput(HWND hWnd) {
	InitInput(hWnd);
	controller = Memory()->alloc<XBOXController>();
}

float Input::GetAxis(std::string_view axisName) {
	float result = 0;
	if (controller->IsConnected()) {

	}
	else {
		if (keyboard.count(axisName.data())) {
			auto& [left, right] = keyboard[axisName.data()];
			bool leftValue = OnKeyHold(left);
			bool rightValue = OnKeyHold(right);
			if (leftValue) result += -1;
			if (rightValue) result += 1;
		}
	}
	return result;
}

float Input::GetRawAxis(std::string_view axisName) {
	return 0;
}

bool Input::GetButton(std::string_view buttonName) {
	return false;
}
