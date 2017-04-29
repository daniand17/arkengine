#include "SceneToRendererSynchronizer.h"

#include "ArkAssert.h"
#include "ArkEngineCore.h"
#include "SceneManager.h"
#include <set>


SceneToRendererSynchronizer::SceneToRendererSynchronizer(RendererContext * context)
	: m_rendererContext(context)
{
	ArkEngineCore * core = ArkEngineCore::Instance();

	subscribeToEvent(NotificationEvent::System_SceneChanged);
	ARK_ASSERT(m_rendererContext != NULL, "No renderer context");
}



void SceneToRendererSynchronizer::onNotify(NotificationEvent const * notifyEvent)
{
	SCOPE_LOCKER(m_rendererContext->getLock(), "Synchronization to renderer");
	doSynchronizationToRenderer();
}



void SceneToRendererSynchronizer::doSynchronizationToRenderer()
{
	Scene * currentScene = ArkEngineCore::Instance()->getSceneManager()->getCurrentScene();
	size_t siz = currentScene->getNumRenderers();

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