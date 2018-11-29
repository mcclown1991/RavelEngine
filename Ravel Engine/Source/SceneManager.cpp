#include "SceneManager.h"

SceneManager * SceneManagement()
{
	static SceneManager s;
	return (&s);
}

SceneManager::SceneManager()
{
}

void SceneManager::Init()
{
	m_currentScene = std::make_pair<unsigned int, Scene*>(0, nullptr);
}

void SceneManager::Update()
{
}

void SceneManager::LoadScene(unsigned int sceneIndex)
{
	//Unload current scene
	if(m_currentScene.second != nullptr)
		m_currentScene.second->Free();

	if (_scenelist.size() == 0) return;

	m_currentScene.first = sceneIndex;
	m_currentScene.second = _scenelist[sceneIndex];
	m_currentScene.second->Init();
	m_currentScene.second->Load();
}

void SceneManager::AddScene(Scene* scene)
{
	_scenelist[_scenelist.size()] = scene;
}

void SceneManager::OnExit()
{
	for (auto& iter : _scenelist) {
		iter.second->~Scene();
	}
}

std::vector<size_t> SceneManager::GetSceneObjects()
{
	std::vector<size_t> objectsids = m_currentScene.second->GetSceneObjects();
	return objectsids;
}

