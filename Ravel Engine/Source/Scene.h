#pragma once

#include <string>
#include <fstream>
#include <rapidjson\document.h>
#include <rapidjson\istreamwrapper.h>

#include <vector>

#include "Factory.h"

class Scene {
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Free() = 0;
	virtual void Load() {
		// load scene file
		std::ifstream json;
		json.open("GameData\\" + _path + _sceneName + ".scene");
		rapidjson::IStreamWrapper isw(json);
		rapidjson::Document doc;
		doc.ParseStream(isw);

		if (doc.IsObject()) {
			rapidjson::Value& root = doc["Scene"];

			unsigned child = root["Object"].GetUint();
			_sceneObjects.reserve(child);

			for (unsigned i = 0; i < child; ++i) {
				// load gameobject
				size_t id = factory()->LoadFromFile(root[std::to_string(i).c_str()].GetString());
				_sceneObjects.push_back(id);
			}
		}
		else {
			std::cout << "Failed to load scene " << "GameData\\" + _path + _sceneName + ".scene" << std::endl;
			std::cout << "Error  : " << doc.GetParseError() << '\n'
				<< "Offset : " << doc.GetErrorOffset() << '\n';

		}
	}

	void Reset() { _sceneObjects.clear(); }
	virtual std::vector<size_t> GetSceneObjects() {
		return _sceneObjects;
	}

#undef SendMessage
	virtual void Start() {
		for (size_t id : _sceneObjects) {
			factory()->GetGameObject(id)->SendMessage("Start");
		}
	}

protected:
	std::string _path;
	std::string _sceneName;
	unsigned int _sceneIndex;
	std::vector<size_t> _sceneObjects;
};