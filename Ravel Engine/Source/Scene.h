#pragma once

#include <string>
#include <fstream>
#include <rapidjson\document.h>
#include <rapidjson\istreamwrapper.h>

#include "Factory.h"

class Scene {
public:
	Scene() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Free() = 0;
	virtual void Load() {
		// load scene file
		std::ifstream json;
		json.open(_path + _sceneName + ".scene");
		rapidjson::IStreamWrapper isw(json);
		rapidjson::Document doc;
		doc.ParseStream(isw);

		if (doc.IsObject()) {
			rapidjson::Value& root = doc["Scene"];

			unsigned child = root["Object"].GetUint();

			for (unsigned i = 0; i < child; ++i) {
				// load gameobject
				factory()->LoadFromFile(root[std::to_string(i).c_str()].GetString());
			}
		}
	}

protected:
	std::string _path;
	std::string _sceneName;
	unsigned int _sceneIndex;
};