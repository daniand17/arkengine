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
	unsigned int siz = currentScene->getNumRenderers();

	Scene::MeshRendererIterator iter = currentScene->getRendererIterator();

	while ( iter != currentScene->getEnd() )
	{
		MeshRenderer * renderer = (*iter);
		if ( !renderer->isSynchronized() )
		{
			ArkRendering::MaterialInfo * mat = renderer->getMaterial();

			RendererContext::AllocatedModel * model = m_rendererContext->getModelForPopulate();
			model->material = mat;
			model->mesh = renderer->getMesh();
			model->modelMatrix = renderer->getTransform()->getModelMatrix();

			renderer->setSynchronized(true);
			iter++;
		}
	}
}