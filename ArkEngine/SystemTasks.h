#pragma once
#include "ArkThread.h"
#include "SceneManager.h"
class SystemTask : public ArkThreading::WorkerTask
{
public:
	SystemTask() {}

protected:
	void init() override;
	void run() override;

private:
	Scene * m_currentScene;
};