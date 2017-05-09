#include "Scene.h"
#include "ArkEngineCore.h"

void Scene::instantiateGameObject(GameObject const * gameObject)
{
	GameObject * newGameObject = new GameObject(gameObject);

	Renderer * ren = newGameObject->getComponent<Renderer>();

	if ( ren )
	{
		m_renderers.push_back(ren);
		m_gameObjects.push_back(newGameObject);
	}
	// NOTE (AD) This is where we might push back colliders
}



void Scene::destroyGameObject(GameObject * gameObject)
{
}



void Scene::serialize(ArkString absFilepath) const
{
	std::vector<SerializableRelationship> sceneObjects = flattenTree();

	ArkString sceneContents("");

	for ( std::vector<SerializableRelationship>::const_iterator it(sceneObjects.begin()); it != sceneObjects.end(); it++ )
	{
		sceneContents += YAML_Generator::genObjectHeader(it->serializableItem->getClassId(), it->fileId);
		sceneContents += it->serializableItem->serialize();
		sceneContents += YAML_Generator::genNumberProperty("m_parentId", it->parentId);
		sceneContents += "\n";
	}

	ArkFile file(absFilepath);
	if ( !file.exists() )
	{
		file.mkfile();
	}
	file.writeToFile(sceneContents);
}



void Scene::deserialize(ArkString absFilepath) const
{
	std::vector<SerializableRelationship> sceneObjects;
	ArkFile sceneFile(absFilepath);

	ArkStringList sceneContents;

	ArkStringList objectList;

	if ( sceneFile.exists() )
	{
		ArkString scene = sceneFile.readAll();
		sceneContents = scene.split('\n');

		ArkString obj("");

		for ( size_t i = 0 ; i < sceneContents.size() ; i++ )
		{
			if ( sceneContents.at(i).contains("---") && obj.length() > 0 )
			{
				// There is a complete object
				objectList.push_back(obj);
				obj = sceneContents.at(i);
			}
			else
			{
				obj += "\n" + sceneContents.at(i);
			}
		}

		if ( obj.length() > 0 )
		{
			objectList.push_back(obj);
		}

	}
}



ArkString Scene::getResourceFileExtension() const
{
	return "scene";
}



std::vector<SerializableRelationship> Scene::flattenTree() const
{
	std::vector<SerializableRelationship> objs;

	unsigned currId(0);

	for ( std::vector<GameObject *>::const_iterator it(m_gameObjects.begin()) ; it != m_gameObjects.end() ; it++ )
	{
		flattenTree(*it, objs, currId, 0);
	}

	return objs;
}



void Scene::flattenTree(GameObject const * obj, std::vector<SerializableRelationship> & currResult, unsigned & id, unsigned parentId) const
{
	SerializableRelationship sr(++id, parentId, obj);
	currResult.push_back(sr);

	SerializableRelationship trans(++id, sr.fileId, obj->getTransform());
	currResult.push_back(trans);

	std::list<Component *> comps = obj->getAllComponents();
	for ( std::list<Component *>::const_iterator it(comps.begin()) ; it != comps.end() ; it++ )
	{
		SerializableRelationship src(++id, sr.fileId, *it);
		currResult.push_back(src);
	}

	std::list<GameObject *> gos = obj->getChildren();
	for ( std::list<GameObject *>::const_iterator it(gos.begin()) ; it != gos.end() ; it++ )
	{
		flattenTree(*it, currResult, id, sr.fileId);
	}
}