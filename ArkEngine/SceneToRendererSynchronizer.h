#pragma once
#include "SystemNotifications.h"

#include "RendererContext.h"

class SceneToRendererSynchronizer : public NotificationSubscriber
{
public:
	SceneToRendererSynchronizer();

	void onNotify(SystemNotifications::ServiceTypes notifiedBy) override;

private:
	void doSynchronizationToRenderer();

	RendererContext * m_rendererContext;
	

};