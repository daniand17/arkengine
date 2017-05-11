#include "Scene.h"
#include "ArkEngineCore.h"
#include "Light.h"
#include "Renderer.h"

Scene::Scene(ArkString name, ArkString filename)
	: ProjectResource(name, filename, RT_Scene)
{

}



Scene::~Scene()
{
	for ( std::vector<GameObject *>::iterator it(m_gameObjects.begin()); it != m_gameObjects.end(); it++ )
	{
		delete *it;
	}
	m_gameObjects.clear();
	m_renderers.clear();
}



void Scene::addGameObjectToScene(GameObject * gameObject)
{

	for ( std::vector<GameObject *>::const_iterator it(m_gameObjects.begin()); it != m_gameObjects.end(); it++ )
	{
		if ( *it == gameObject )
		{
			return;
		}
	}

	Renderer * ren = gameObject->getComponent<Renderer>();

	if ( ren )
	{
		m_renderers.push_back(ren);
		m_gameObjects.push_back(gameObject);
	}

	// NOTE (AD) This is where we might push back colliders?
}



void Scene::destroyGameObject(GameObject * gameObject)
{
}



void Scene::serialize() const
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

	ArkFile file(m_filename);
	if ( !file.exists() )
	{
		file.mkfile();
	}
	file.writeToFile(sceneContents);
}



void Scene::deserialize()
{
	ArkStringList objectList;
	getSceneObjectsForDeserialize(m_filename, objectList);

	std::vector<SerializableRelationship> objs = genFlattenedObjectTree(objectList);

	std::vector<GameObject *> gos = unflattenObjectTree(objs);

	clearScene();

	m_gameObjects = gos;

	for ( std::vector<GameObject *>::iterator goIt(gos.begin()) ; goIt != gos.end() ; goIt++ )
	{
		std::list<Renderer *> rens = (*goIt)->getComponentsInChildren<Renderer>();

		for ( std::list<Renderer *>::iterator renIt(rens.begin()); renIt != rens.end() ; renIt++ )
		{
			bool isInList = false;
			for ( std::vector<Renderer *>::iterator rIt(m_renderers.begin()); rIt != m_renderers.end(); rIt++ )
			{
				if ( *rIt == *renIt )
				{
					isInList = true;
					break;
				}
			}

			if ( !isInList )
			{
				m_renderers.push_back(*renIt);
			}
		}
	}
}


std::vector<GameObject *> Scene::unflattenObjectTree(std::vector<SerializableRelationship> &objs) const
{
	std::vector<GameObject *> gos;

	for ( size_t i = 0 ; i < objs.size() ; i++ )
	{
		SerializableRelationship & currObj = objs.at(i);

		if ( currObj.parentId == 0 && currObj.serializableItem->getClassId() == I_Serializable::CI_GameObject )
		{
			gos.push_back(dynamic_cast<GameObject *>(currObj.serializableItem));
		}

		for ( size_t k = 0; k < objs.size() ; k++ )
		{
			SerializableRelationship & parent = objs.at(k);

			if ( parent.fileId == currObj.parentId && parent.serializableItem->getClassId() == I_Serializable::CI_GameObject )
			{

				GameObject * parentObj = dynamic_cast<GameObject *>(parent.serializableItem);
				switch ( currObj.serializableItem->getClassId() )
				{
				case I_Serializable::CI_GameObject:
					parentObj->addChild(dynamic_cast<GameObject *>(currObj.serializableItem));
					break;
				case I_Serializable::CI_Transform:
					parentObj->setTransform(dynamic_cast<Transform *>(currObj.serializableItem));
					break;
				default:
					parentObj->transferComponentToObject(dynamic_cast<Component *>(currObj.serializableItem));
					break;
				}
			}
		}
	}

	return gos;
}



std::vector<SerializableRelationship> Scene::genFlattenedObjectTree(ArkStringList &objectList) const
{
	std::vector<SerializableRelationship> sceneObjects;

	for ( size_t i = 0 ; i < objectList.size() ; i++ )
	{
		ArkString currObject(objectList.at(i));
		unsigned classId(0), fileId(0), parentId(0);

		if ( YAML_Extractor::extractObjectHeader(currObject, classId, fileId) )
		{
			ArkString last = currObject.split('\n').getLast();
			if ( YAML_Extractor::extractNumberProperty(last, "m_parentId", parentId) )
			{

				I_Serializable * serializable = NULL;

				switch ( classId )
				{
				case I_Serializable::CI_GameObject:
					serializable = new GameObject();
					break;
				case I_Serializable::CI_Light:
					break;
				case I_Serializable::CI_MeshRenderer:
					serializable = new MeshRenderer();
					break;
				case I_Serializable::CI_Rigidbody:
					serializable = new Rigidbody();
					break;
				case I_Serializable::CI_Transform:
					serializable = new Transform();
					break;
				}

				if ( serializable )
				{
					serializable->deserialize(currObject);
					sceneObjects.push_back(SerializableRelationship(fileId, parentId, serializable));
				}
			}
		}
	}

	return sceneObjects;
}



void Scene::clearScene()
{
	for ( std::vector<GameObject *>::iterator it(m_gameObjects.begin()); it != m_gameObjects.end(); it++ )
	{
		delete *it;
	}

	m_gameObjects.clear();

	for ( std::vector<Renderer *>::iterator it(m_renderers.begin()); it != m_renderers.end(); it++ )
	{
		delete *it;
	}

	m_renderers.clear();
}



void Scene::getSceneObjectsForDeserialize(ArkString &absFilepath, ArkStringList &objectList) const
{
	ArkFile sceneFile(absFilepath);
	if ( sceneFile.exists() )
	{
		ArkStringList sceneContents = sceneFile.readAll().split('\n');
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



void Scene::flattenTree(GameObject * obj, std::vector<SerializableRelationship> & currResult, unsigned & id, unsigned parentId) const
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