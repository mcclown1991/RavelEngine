#pragma once

#include <string>
#include <fstream>
#include <rapidjson\document.h>
#include <rapidjson\istreamwrapper.h>

#include <vector>

#include "Factory.h"
#include "RavelEngine.h"

#undef SendMessage

class Scene {
public:
	Scene() {};
	virtual ~Scene() { _sceneObjects.clear(); };
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Free() { 
		for (size_t id : _sceneObjects) {
			factory()->GetGameObject(id)->SendMessage("OnDestory");
		}
		Memory()->dealloc(this);
		this->~Scene(); 
	};
	virtual void Load() {
		// load scene file
		std::ifstream json;
		json.open(RavelEngine::getGameDataPath().data() + _path + _sceneName + ".scene");
		rapidjson::IStreamWrapper isw(json);
		rapidjson::Document doc;
		doc.ParseStream(isw);

		if (doc.IsObject()) {
			rapidjson::Value& root = doc["Scene"];

			unsigned child = root["Object"].GetUint();
			_sceneObjects.reserve(child);

			for (unsigned i = 0; i < child; ++i) {
				// load gameobject
				size_t id = factory()->LoadFromFile(RavelEngine::getGameDataPath().data() + std::string(root[std::to_string(i).c_str()].GetString()));
				if(id > 0)
					_sceneObjects.push_back(id);
			}
		}
		else {
			std::cout << "Failed to load scene " << RavelEngine::getGameDataPath().data() + _path + _sceneName + ".scene" << std::endl;
			std::cout << "Error  : " << doc.GetParseError() << '\n'
				<< "Offset : " << doc.GetErrorOffset() << '\n';

		}

		json.close();
	}

	void Reset() { _sceneObjects.clear(); }
	virtual std::vector<size_t> GetSceneObjects() {
		return _sceneObjects;
	}

	virtual void Start() {
		for (size_t id : _sceneObjects) {
			factory()->GetGameObject(id)->SendMessage("Start");
		}
	}

	void InternalInit() {
		auto& obj = factory()->CreateGameObject("Main Camera");
		obj->AddComponent("Camera");
		_sceneObjects.push_back(obj->GetInstanceID());
		GetGraphicsManager()->SetMainCamera(obj->GetComponent<Camera>());
	}

protected:
	std::string _path;
	std::string _sceneName;
	unsigned int _sceneIndex;
	std::vector<size_t> _sceneObjects;
};