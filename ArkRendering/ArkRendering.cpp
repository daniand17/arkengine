#include "ArkRendering.h"
#include "ArkAssert.h"
#include "ArkFile.h"


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



void ArkRendering::ModelInfo::serialize(ArkString absFilepath) const
{
	ArkString syncString("");
	syncString += "\n\tname=" + m_name;
	syncString += "\n\tmesh=" + m_mesh;
	syncString += "\n\tmaterial=" + m_material;
	ArkFile file(absFilepath);
	file.writeToFile(syncString);
	// TODO (AD) Serialize Model Info to file
}



void ArkRendering::ModelInfo::deserialize(ArkString absFilepath) const
{

	// TODO (AD) Deserialize model info from file
}
