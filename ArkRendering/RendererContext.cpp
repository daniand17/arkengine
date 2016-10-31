#include "RendererContext.h"
#include "ArkDebug.h"

RendererContext * RendererContext::smInstance = NULL;

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
	for ( vector<AllocatedModel>::const_iterator iter = m_models.begin() ; iter < m_models.end() ; iter++ )
	{
		if ( out.find(iter->material->m_name) == out.end() ) 
			out.insert(iter->material->m_name);
	}
}


void RendererContext::getModelsUsingMaterial(ArkString material, std::vector<AllocatedModel> & out)
{
	SCOPE_LOCKER lock(m_lock, "Get used models with material");
	for ( size_t i = 0 ; i < m_models.size() ; i++ )
	{
		if ( m_models[i].material->m_name == material )
			out.push_back(m_models[i]);
	}
}


bool RendererContext::materialAlreadyInContext(ArkRendering::MaterialInfo * material) const
{
	ArkString matName = material->m_name;

	for ( size_t i = 0 ; i < m_usedMaterials.size() ; i++ )
		if ( matName == m_usedMaterials[i].m_name )
			return true;
		
	return false;
}


void RendererContext::addMaterial(ArkRendering::MaterialInfo const * materialInfo)
{
	m_usedMaterials.push_back(*materialInfo);
}


void RendererContext::addModelToContext(AllocatedModel model)
{
	AllocatedModel newModel;
	newModel.material = model.material;
	newModel.mesh = model.mesh;
	m_models.push_back(model);
}


void RendererContext::clearUnusedMaterials()
{
	// TODO Iterate through the list of models and clear any material that isn't being used
}
