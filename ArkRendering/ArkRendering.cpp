#include "ArkRendering.h"
#include "ImageLoader.h"
#include "ArkAssert.h"

void ArkRendering::LightInfo::bindLightToShader() const
{
	glUniform3f(eyeId, eyePosition.x, eyePosition.y, eyePosition.z);
	glUniform3f(colId, color.x, color.y, color.z);
}



void ArkRendering::LightInfo::getUniformLocationsFromShader(GLuint shaderProgramId)
{
	eyeId = glGetUniformLocation(shaderProgramId, "lightInfo.eyePosition");
	colId = glGetUniformLocation(shaderProgramId, "lightInfo.color");
}



ArkString ArkRendering::ModelInfo::serialize() const
{
	ArkString syncString = "ModelInfo";
	syncString += "\n\tname:" + m_name;
	syncString += "\n\tmesh:" + m_mesh;
	syncString += "\n\tmaterial:" + m_material;
	return syncString;
}