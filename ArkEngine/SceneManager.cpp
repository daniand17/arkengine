#include "SceneManager.h"

SceneManager * SceneManager::sm_instance = 0;

void SceneManager::initialize()
{
	sm_instance = new SceneManager();
}

SceneManager::SceneManager()
{
}
