#include "SceneManager.h"
#include "RavelEngine.h"

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
	m_currentScene = m_NextScene = std::make_pair<unsigned int, Scene*>(-1, nullptr);
}

void SceneManager::Update()
{
	if (m_currentScene.first != m_NextScene.first)
		LoadScene();
}

void SceneManager::LoadScene() {
	//Unload current scene
	if (m_currentScene.second != nullptr) {
		m_currentScene.second->Free();
	}

	if (_scenelist.size() == 0) return;

	m_currentScene.first = m_NextScene.first;
	m_currentScene.second = m_NextScene.second;
	m_currentScene.second->InternalInit();
	m_currentScene.second->Init();
	m_currentScene.second->Load();
	m_currentScene.second->Start();
}

void SceneManager::LoadScene(unsigned int sceneIndex)
{
	m_NextScene.first = sceneIndex;
	m_NextScene.second = _scenelist[sceneIndex];
}

void SceneManager::AddScene(Scene* scene)
{
	_scenelist[_scenelist.size()] = scene;
}

void SceneManager::OnExit()
{
	for (auto& iter : _scenelist) {
		iter.second->Free();
	}
}

void SceneManager::Restart()
{
	m_currentScene.second->Reset();
	RavelEngine::GetRavelEngine()->ResetScene();
}

std::vector<size_t> SceneManager::GetSceneObjects()
{
	std::vector<size_t> objectsids = m_currentScene.second->GetSceneObjects();
	return objectsids;
}

