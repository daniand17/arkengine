#pragma once
#include <vector>
#include "Filesystem.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

class SceneManager : public NotificationSubscriber
{
public:
	SceneManager();
	void setSceneDirectory(ArkString path ) { m_scenePath = path; }
	void openSceneByName(ArkString sceneName);
	void closeCurrentOpenScene();
	
	ArkString getSceneDirectory() const { return m_scenePath; }
	Scene * getCurrentScene() const { return m_currentScene; }

private:
	Scene * m_currentScene;
	ArkString m_scenePath;

	// Inherited via NotificationSubscriber
	virtual void onNotify(NotificationEvent const * type) override;
};