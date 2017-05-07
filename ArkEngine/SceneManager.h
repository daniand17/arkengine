#pragma once
#include <vector>
#include "ArkDirectory.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

class SceneManager : public NotificationSubscriber
{
public:
	SceneManager();
	void openSceneByName(ArkString sceneName);
	void closeCurrentOpenScene();
	
	Scene * getCurrentScene() const { return m_currentScene; }

private:
	Scene * m_currentScene;

	// Inherited via NotificationSubscriber
	virtual void onNotify(NotificationEvent const * type) override;

	ArkString getScenePath() const;
};