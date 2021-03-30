#include "Input.h"
#include "MemoryManager.h"

#include <string>

using namespace std::string_literals;

XBOXController* Input::controller = nullptr;
std::map<std::string, InputBinding*> Input::keyboard = std::map<std::string, InputBinding*>();

Input* GetInput() {
	static Input s;
	return(&s);
}

Input::Input() {
}

Input::~Input() {
	controller->~XBOXController();
	for(auto const& elem : keyboard) {
		elem.second->~InputBinding();
		Memory()->dealloc(elem.second);
	}
}

void Input::InitializeInput(HWND hWnd) {
	InitInput(hWnd);
	stringToKeyDefines.emplace("left"s, RK_LEFT);
	stringToKeyDefines.emplace("right"s, RK_RIGHT);
	stringToKeyDefines.emplace("up"s, RK_UP);
	stringToKeyDefines.emplace("down"s, RK_DOWN);
	stringToKeyDefines.emplace("w"s, RK_W);
	stringToKeyDefines.emplace("a"s, RK_A);
	stringToKeyDefines.emplace("s"s, RK_S);
	stringToKeyDefines.emplace("d"s, RK_D);
	controller = Memory()->alloc<XBOXController>();

	std::ifstream json;
	json.open("InputManager.input");
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		rapidjson::Value& input = doc["InputManager"];
		for(rapidjson::Value::ConstMemberIterator it = input.MemberBegin(); it != input.MemberEnd(); ++it) {
			auto* inputBind = Memory()->alloc<InputBinding>();
			inputBind->description = it->value["description"].GetString();
			auto strContainer = it->value["negative"].GetString();
			auto keyBind = stringToKeyDefines.at(strContainer);
			inputBind->negative = keyBind;
			strContainer = it->value["positive"].GetString();
			keyBind = stringToKeyDefines.at(strContainer);
			inputBind->positive = keyBind;
			strContainer = it->value["alternate positive"].GetString();
			keyBind = stringToKeyDefines.at(strContainer);
			inputBind->alt_positive = keyBind;
			strContainer = it->value["alternate negative"].GetString();
			keyBind = stringToKeyDefines.at(strContainer);
			inputBind->alt_negative = keyBind;
			inputBind->invert = it->value["invert"].GetBool();
			//type need conversion
			keyboard.emplace(std::pair(it->name.GetString(), inputBind));
		}
	}

	json.close();
}

float Input::GetAxis(std::string_view axisName) {
	float result = 0;
	if (controller->IsConnected()) {

	}
	else {
		if (keyboard.count(axisName.data())) {
			auto& inputBind = keyboard[axisName.data()];
			auto const leftValue = OnKeyHold(inputBind->negative);
			auto const rightValue = OnKeyHold(inputBind->positive);
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
