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
		{"w"s, RK_W},
		{"a"s, RK_A},
		{"s"s, RK_S},
		{"d"s, RK_D}
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
				auto const& key = itr->GetObjectW();
				auto const& keystroke = stringToKeyDefines.at(key["key"].GetString());
				axisMapping[name].push_back(std::pair(keystroke, key["scale"].GetFloat()));
			}
		}
	}

	json.close();
}

void Input::Update() {
	for(auto const& [axis, function] : axisFunction) {
		if (!axisMapping.count(axis))
			continue;
		auto const& axisInfo = axisMapping.at(axis);
		float total_scale = 0;
		for(auto const& [keystroke, scale] : axisInfo) {
			if(OnKeyHold(keystroke)) {
				function(scale);
				total_scale += scale;
			}
		}
	}
}

void Input::BindAxis(std::string_view axis, std::function<void(float)> const& function) {
	axisFunction.emplace_back(std::pair(axis.data(), function));
}

void Input::BlindAction(std::string_view action, std::function<void()> const& function) {
	
}
