#include "SceneToRendererSynchronizer.h"

#include "ArkAssert.h"
#include "ArkEngineCore.h"
#include "SceneManager.h"
#include <set>

SceneToRendererSynchronizer::SceneToRendererSynchronizer()
{
	ArkEngineCore * core = ArkEngineCore::Instance();
	SystemNotificationBus * bus = core ? core->getNotificationBus() : NULL;

	ARK_ASSERT(bus != NULL, "No notification bus or engine core");
	core->getNotificationBus()->attachSubscriber(this, SystemNotifications::OnSceneChanged);

	m_rendererContext = RendererContext::Instance();

	ARK_ASSERT(m_rendererContext != NULL, "No renderer context");
}

void SceneToRendererSynchronizer::onNotify(SystemNotifications::ServiceTypes notifiedBy)
{
	SCOPE_LOCKER(m_rendererContext->getLock(), "Synchronization to renderer");
	doSynchronizationToRenderer();
}

void SceneToRendererSynchronizer::doSynchronizationToRenderer()
{
	Scene * currentScene = ArkEngineCore::Instance()->getSceneManager()->getCurrentScene();
	size_t siz = currentScene->getNumRenderers();

	Scene::SceneRendererIterator iter = currentScene->getRendererIterator();

	bool addedModelsToRendererContext = false;

	for ( size_t i = 0 ; i < siz; i++, iter++ )
	{
		ArkRendering::MaterialInfo  * mat = (*iter)->getMaterial();
		if ( !m_rendererContext->materialAlreadyInContext(mat) )
		{
			m_rendererContext->addMaterial(mat);
			addedModelsToRendererContext = true;
		}

		RendererContext::AllocatedModel model;
		model.material = mat;
		model.mesh = (*iter)->getMesh();

		m_rendererContext->addModelToContext(model);
		addedModelsToRendererContext = true;
	}



}
