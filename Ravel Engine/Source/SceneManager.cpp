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
}

void SceneManager::Update()
{
}

void SceneManager::LoadScene(Scene* scene)
{
	//Unload current scene
}

void SceneManager::LoadScene(int sceneIndex)
{
	//Unload current scene
	if(m_currentScene != nullptr)
		m_currentScene->Free();

	m_currentScene = _scenelist[sceneIndex];
	m_currentScene->Init();
	m_currentScene->Load();
}

void SceneManager::AddScene(Scene* scene)
{
	_scenelist[_scenelist.size()] = scene;
}

