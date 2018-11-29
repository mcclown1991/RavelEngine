#pragma once
#include "Scene.h"
#include <map>
//#include <utility>
#include <string>

class SceneManager {
public:
	SceneManager();
	void Init();
	void Update();
	void LoadScene(unsigned int sceneIndex);
	void AddScene(Scene* scene);

	unsigned GetLoadedSceneIndex() { return m_currentScene.first; }

	template <typename T>
	void AddScene();

	void OnExit();

	std::vector<size_t> GetSceneObjects();
private:
	typedef std::pair<unsigned, Scene* > SceneBlock;

	SceneBlock m_currentScene;
	SceneBlock m_NextScene;
	std::map <unsigned int, Scene* > _scenelist;
};

SceneManager* SceneManagement();

template<typename T>
void SceneManager::AddScene()
{
	T* scene = dynamic_cast<T*>(Memory()->alloc<T>());
	_scenelist[_scenelist.size()] = scene;
}
