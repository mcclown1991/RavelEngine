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
	void LoadScene(Scene* scene);
	void LoadScene(int sceneIndex);
	void AddScene(Scene* scene);

	template <typename T>
	void AddScene();
private:
	Scene* m_currentScene;
	Scene* m_NextScene;
	std::map <unsigned int, Scene* > _scenelist;
};

SceneManager* SceneManagement();

template<typename T>
void SceneManager::AddScene()
{
	T* scene = dynamic_cast<T*>(Memory()->alloc<T>());
	_scenelist[_scenelist.size()] = scene;
}
