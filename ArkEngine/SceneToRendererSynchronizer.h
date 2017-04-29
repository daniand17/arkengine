#pragma once
#include "SystemNotifications.h"

#include "RendererContext.h"

class SceneToRendererSynchronizer : public NotificationSubscriber
{
public:
	SceneToRendererSynchronizer(RendererContext * context);

	void onNotify(NotificationEvent const * notifyEvent) override;

private:
	void doSynchronizationToRenderer();

	RendererContext * m_rendererContext;
	

};