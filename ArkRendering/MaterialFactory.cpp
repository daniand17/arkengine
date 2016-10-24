#include "MaterialFactory.h"

#include "Filestream.h"

using namespace ArkRendering;

Resource_Id MaterialFactory::CreateMaterial()
{
	MaterialInfo * material = new MaterialInfo();
	material->id = mLoadedMaterials.size();
	material->ambient = Vec3(1, 1, 1);
	material->diffuse = Vec3(1, 1, 1);
	material->specular = Vec3(1, 1, 1);
	material->shininess = 32;

	mLoadedMaterials.push_back(material);

	return material->id;
}

void MaterialFactory::SynchronizeResources(ArkString projectName)
{
	Filestream filestream(projectName, "materials");
	filestream.OpenFile(Filestream::FileOpenType::Write);

	ArkString syncString = "";

	for ( MaterialInfoListT::const_iterator iter = mLoadedMaterials.begin() ; iter < mLoadedMaterials.end() ; iter++ )
	{
		syncString += (*iter)->Synchronize();
		if ( (iter + 1) != mLoadedMaterials.end() )
			syncString += ",";
	}

	filestream.WriteStringToFile(syncString);
	filestream.CloseFile();
}

void MaterialFactory::DesynchronizeResources(ArkString projectName)
{
	Filestream filestream(projectName, "materials");
	try { filestream.OpenFile(Filestream::FileOpenType::Read); }
	catch ( std::exception & e ) { e.what(); }

	ArkString fileContents = "";
	filestream.ReadAll(&fileContents);
	filestream.CloseFile();
	if ( fileContents.length() > 0 )
	{
		ArkStringList materialList = fileContents.split(',');
		for ( size_t i = 0 ; i < materialList.size() ; i++ )
			createMaterialFromString(materialList.at(static_cast<unsigned>(i)));
	}
}

void MaterialFactory::clear()
{
	while ( mLoadedMaterials.size() > 0 )
	{
		MaterialInfo * matInfo = mLoadedMaterials[mLoadedMaterials.size() - 1];
		delete matInfo;
		mLoadedMaterials.pop_back();
	}
}

void MaterialFactory::createMaterialFromString(ArkString & materialString)
{
	if ( materialString.length() == 0 ) return;
	ArkStringList list = materialString.split('\n');
	MaterialInfo * material = new MaterialInfo();

	int matId = 0;
	sscanf_s(list.at(1).c_str(), "\tresourceId\t%d", &matId);
	material->id = static_cast<Resource_Id>(matId);

	sscanf_s(list.at(2).c_str(), "\tambient \tVec3(%f %f %f)", &(material->ambient.x), &(material->ambient.y), &(material->ambient.z));
	sscanf_s(list.at(3).c_str(), "\tdiffuse \tVec3(%f %f %f)", &(material->diffuse.x), &(material->diffuse.y), &(material->diffuse.z));
	sscanf_s(list.at(4).c_str(), "\tspecular \tVec3(%f %f %f)", &(material->specular.x), &(material->specular.y), &(material->specular.z));
	sscanf_s(list.at(5).c_str(), "\tshininess \t%f", &(material->shininess));

	int shaderProgramId = 0;
	sscanf_s(list.at(6).c_str(), "\tshaderId \t%d", &(shaderProgramId));
	material->setShaderProgram(shaderProgramId, false);
	mLoadedMaterials.push_back(material);

	// TODO (AD) Do asserts that check number of floats found per string or throw an exception to be handled?
	// this exception would be something along the lines of "corrupted materials file exception"
}
