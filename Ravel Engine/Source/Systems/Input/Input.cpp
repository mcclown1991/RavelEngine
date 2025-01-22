#include "Input.h"
#include "MemoryManager.h"

#include <string>
#include <algorithm>

using namespace std::string_literals;

XBOXController* Input::controller = nullptr;

Input* GetInput() {
	static Input s;
	return(&s);
}

Input::Input() {
}

Input::~Input() {
	controller->~XBOXController();
}

void Input::InitializeInput(HWND hWnd) {
	InitInput(hWnd);

	stringToKeyDefines = {
		{"left"s, RK_LEFT},
		{"right"s, RK_RIGHT},
		{"up"s, RK_UP},
		{"down"s, RK_DOWN},

		{"a"s, RK_A},
		{"b"s, RK_B},
		{"c"s, RK_C},
		{"d"s, RK_D},
		{"e"s, RK_E},
		{"f"s, RK_F},
		{"g"s, RK_G},
		{"h"s, RK_H},
		{"i"s, RK_I},
		{"j"s, RK_J},
		{"k"s, RK_K},
		{"l"s, RK_L},
		{"m"s, RK_M},
		{"n"s, RK_N},
		{"o"s, RK_O},
		{"p"s, RK_P},
		{"q"s, RK_Q},
		{"r"s, RK_R},
		{"s"s, RK_S},
		{"t"s, RK_T},
		{"u"s, RK_U},
		{"v"s, RK_V},
		{"w"s, RK_W},
		{"x"s, RK_X},
		{"y"s, RK_Y},
		{"z"s, RK_Z},

		{"escape"s, RK_ESC},
		{"space"s, RK_SPACE},
		{"page up"s, RK_PAGEUP},
		{"page down"s, RK_PAGEDOWN},
		{"end"s, RK_END},
		{"home"s, RK_HOME},
		{"return"s, RK_RETURN},

		{"left shift"s, RK_RETURN},
		{"right shift"s, RK_RETURN},
		{"left control"s, RK_RETURN},
		{"right control"s, RK_RETURN},

		{"Gamepad Left Thumbstick Y-Axis", RC_L_STICK_Y},
		{"Gamepad Left Thumbstick X-Axis", RC_L_STICK_X}
	};

	controller = Memory()->alloc<XBOXController>();

	std::ifstream json;
	json.open("InputManager.input");
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		rapidjson::Value& axis = doc["Axis"];
		for (rapidjson::Value::ConstMemberIterator it = axis.MemberBegin(); it != axis.MemberEnd(); ++it) {
			auto const& name = it->name.GetString();
			auto& binding = it->value["binding"];
			for (rapidjson::Value::ConstValueIterator itr = binding.Begin(); itr != binding.End(); ++itr) {
				auto const& key = itr->GetObject();
						
				if (stringToKeyDefines.count(key["key"].GetString())) {
					auto const& keystroke = stringToKeyDefines.at(key["key"].GetString());
					axisMapping[name].push_back(std::pair(keystroke, key["scale"].GetFloat()));
				}
			}
		}
	}

	json.close();
}

void Input::Update() {
	for (auto const& [id, axisVector] : axisFunction) {
		for (auto const& [axis, function] : axisVector) {
			if (!axisMapping.count(axis))
				continue;
			auto const& axisInfo = axisMapping.at(axis);
			float total_scale = 0;
			for (auto const& [keystroke, scale] : axisInfo) {
				if (keystroke < 0x10) {
					// gamepad
					total_scale = controller->GetAxis(keystroke);
					function(total_scale * scale);
				}
				else {
					if (OnKeyHold(keystroke)) {
						function(scale);
					}
				}
			}
		}
	}

	for(auto const& [id, actionsVector] : actionFunction) {
		for(auto const& [action, function] : actionsVector) {
			if (!actionMapping.count(action))
				continue;
			auto const& actionInfo = actionMapping.at(action);
			for(auto const& keystroke : actionInfo) {
				if (OnKeyHold(keystroke) || controller->IsPressed(keystroke)) {
					function();
				}
			}
		}
	}
}

void Input::BindAxis(std::string_view axis, size_t instance, std::function<void(float)> const& function) {
	if (!axisFunction.count(instance))
		axisFunction[instance] = std::vector<std::pair<std::string, std::function<void(float)>>>();
	axisFunction[instance].emplace_back(std::pair(axis.data(), function));
}

void Input::BlindAction(std::string_view action, size_t instance, std::function<void()> const& function) {
	if (!actionFunction.count(instance))
		actionFunction[instance] = std::vector<std::pair<std::string, std::function<void()>>>();
	actionFunction[instance].emplace_back(std::pair(action.data(), function));
}

void Input::UnbindAxis(std::string_view axis, size_t instance) {
	if(axisFunction.count(instance)) {
		axisFunction[instance].clear();
		axisFunction.erase(instance);
	}
}

void Input::UnBindAction(std::string_view action, size_t instance) {
	if (actionFunction.count(instance)) {
		actionFunction[instance].clear();
		actionFunction.erase(instance);
	}
}
