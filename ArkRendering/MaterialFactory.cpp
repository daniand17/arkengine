#include "MaterialFactory.h"
#include "MaterialFactory.h"

#include "Filestream.h"

using namespace ArkRendering;

void MaterialFactory::CreateMaterial(ArkString name, ArkString shaderName)
{
	MaterialInfo newMat;
	newMat.m_name = name;
	newMat.ambient = Vec3(1, 1, 1);
	newMat.diffuse = Vec3(1, 1, 1);
	newMat.specular = Vec3(1, 1, 1);
	newMat.shininess = 32;
	newMat.setShader(shaderName);
	m_loadedMaterials.insert(MaterialNamePair(name, newMat));
}



void MaterialFactory::serializeResources()
{
	ArkString syncString = "";
	for ( MaterialCollection::iterator iter = m_loadedMaterials.begin() ; iter != m_loadedMaterials.end() ; iter++ )
	{
		if ( iter != m_loadedMaterials.begin() )
			syncString += "\n,";
	
		syncString += iter->second.serialize();
	}

	ArkFile * metafile;
	ArkDirectory dir(m_resourcePath);
	if ( dir.fileExists("materials.meta") )
	{
		metafile = dir.getFileByFilename("materials.meta");
	}
	else
	{
		metafile = dir.createFile("materials", "meta");
	}

	metafile->writeToFile(syncString);
}



void MaterialFactory::deserializeResources()
{
	ArkDirectory dir(m_resourcePath);
	if ( !dir.fileExists("materials.meta") ) return;
	// TODO maybe eventually read from file list?
	ArkFile * infile = dir.getFileByFilename("materials.meta");
	ArkString fileContents = infile->getFileContents();

	if ( fileContents.length() > 0 )
	{
		ArkStringList materialList = fileContents.split(',');
		for ( unsigned int i = 0 ; i < materialList.size() ; i++ )
			createMaterialFromString(materialList.at(static_cast<unsigned>(i)));
	}
}



ArkRendering::MaterialInfo * MaterialFactory::getResourceByName(ArkString name)
{
	auto iter = m_loadedMaterials.find(name);
	return iter != m_loadedMaterials.end() ? &(iter->second) : NULL;
}



void MaterialFactory::getAllMaterials(std::vector<ArkRendering::MaterialInfo*>& out)
{
	for ( auto i = m_loadedMaterials.begin() ; i != m_loadedMaterials.end() ; i++ )
		out.push_back(&(i->second));
}



void MaterialFactory::createMaterialFromString(ArkString & materialString)
{
	if ( materialString.length() == 0 ) return;
	ArkStringList list = materialString.split('\n');
	MaterialInfo material;
	// TODO (AD) make sure that a material with this name doesn't already exist
	
	material.m_name = list.at(1).split(':').getLast();
	sscanf_s(list.at(2).c_str(), "\tambient:Vec3(%f %f %f)", &(material.ambient.x), &(material.ambient.y), &(material.ambient.z));
	sscanf_s(list.at(3).c_str(), "\tdiffuse:Vec3(%f %f %f)", &(material.diffuse.x), &(material.diffuse.y), &(material.diffuse.z));
	sscanf_s(list.at(4).c_str(), "\tspecular:Vec3(%f %f %f)", &(material.specular.x), &(material.specular.y), &(material.specular.z));
	sscanf_s(list.at(5).c_str(), "\tshininess:%f", &(material.shininess));

	material.setShader(list.at(6).split(':').getLast());

	m_loadedMaterials.insert(MaterialNamePair(material.m_name, material));

	// TODO (AD) Do asserts that check number of floats found per string or throw an exception to be handled?
	// this exception would be something along the lines of "corrupted materials file exception"
}