#include "RendererContext.h"
#include "ArkDebug.h"

using namespace ArkRendering;
using namespace std;

RendererContext::RendererContext()
	: m_isDirty(true)
	, m_lock(NULL)
{
	m_lock = new ArkThreading::ArkMutex();
	Debug::Log("Initialized RendererModelManager");
}



RendererContext::~RendererContext()
{
	delete m_lock;
	m_lock = 0;
}



void RendererContext::getUsedMaterials(std::set<ArkString> & out) const
{
	out.clear();
	SCOPE_LOCKER lock(m_lock, "Get used materials");
	for ( ModelList::const_iterator citer = m_models.begin() ; citer != m_models.end() ; citer++ )
	{
		AllocatedModel * model = *citer;
		if ( out.find(model->material->m_name) == out.end() )
			out.insert(model->material->getShaderName());
	}
}



void RendererContext::getModelsUsingMaterial(ArkString material, std::vector<AllocatedModel *> & out)
{
	SCOPE_LOCKER lock(m_lock, "Get used models with material");
	for ( ModelList::const_iterator citer = m_models.begin() ; citer != m_models.end() ; citer++ )
	{
		if ( (*citer)->material->m_name == material )
			out.push_back(*citer);
	}
}



RendererContext::AllocatedModel * RendererContext::getModelForPopulate()
{
	m_isDirty = true;
	AllocatedModel * newModel;
	if ( m_freeModels.size() == 0 )
	{
		newModel = new AllocatedModel();
	}
	else
	{
		newModel = m_freeModels.front();
		m_freeModels.pop_front();
	}

	m_models.push_back(newModel);
	return newModel;
}


void RendererContext::clearUnusedMaterials()
{
	// TODO Iterate through the list of models and clear any material that isn't being used
}
