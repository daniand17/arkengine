#include "MaterialResource.h"
#include "ShaderFactory.h"
#include "OpenGLRenderer.h"
#include "ArkFile.h"


MaterialResource::MaterialResource(ArkString name, ArkString filename)
	: ProjectResource(name, filename, RT_Material)
{

}



void MaterialResource::createRenderPass(ShaderResource const * vertexShader, ShaderResource const * fragmentShader)
{
	ShaderFactory * fac = OpenGLRenderer::Instance()->getShaderFactory();
	ShaderProgram const * program;

	if ( fac->hasShaderProgramForShaders(vertexShader, fragmentShader) )
	{
		program = fac->getProgramForShaders(vertexShader, fragmentShader);
	}
	else
	{
		program = fac->createShaderProgram(vertexShader, fragmentShader);
	}

	if ( program )
	{
		m_renderPasses.push_back(new RenderPass(program));
	}
}



void MaterialResource::serialize() const
{
	// TODO (AD) serialize material resource
}



void MaterialResource::deserialize()
{

	ArkStringList renderPasses;

	genRenderPassInfo(renderPasses);

	std::vector<RenderPass *> rpObjs(renderPasses.size());
	for ( size_t i = 0 ; i < renderPasses.size() ; i++ )
	{
		ArkStringList rpLines(renderPasses.at(i).split('\n'));

		ArkString vertexShader(""), fragmentShader("");

		for ( size_t k = 0 ; k < rpLines.size(); k++ )
		{
			ArkString line(rpLines.at(k));
			ArkString prop("");
			if ( YAML_Extractor::extractStringProperty(line, "m_vertex", prop) )
			{
				vertexShader = prop;
			}
			else if ( YAML_Extractor::extractStringProperty(line, "m_fragment", prop) )
			{
				fragmentShader = prop;
			}
		}


		if ( vertexShader.length() > 0 && fragmentShader.length() > 0 )
		{
			ShaderFactory * fac = OpenGLRenderer::Instance()->getShaderFactory();
			ShaderResource const * vert = fac->getShaderByName(vertexShader);
			ShaderResource const * frag = fac->getShaderByName(fragmentShader);

			RenderPass * pass(NULL);

			if ( fac->hasShaderProgramForShaders(vert, frag) )
			{
				pass = new RenderPass(fac->getProgramForShaders(vert, frag));
			}
			else
			{
				pass = new RenderPass(fac->createShaderProgram(vert, frag));
			}

			if ( pass )
			{
				rpObjs.push_back(pass);
			}
		}
	}

	// TODO (AD) deserialize material resource
}



void MaterialResource::genRenderPassInfo(ArkStringList &renderPasses)
{
	ArkFile file(m_filename);
	ArkString contents(file.readAll());
	ArkStringList lines = contents.split('\n');
	ArkString renderPassObject("");

	for ( size_t i = 0 ; i < lines.size(); i++ )
	{
		ArkString line(lines.at(i));
		if ( line == "RenderPass:" )
		{
			if ( i > 0 )
			{
				renderPasses.push_back(renderPassObject);
				renderPassObject = "";
			}
		}
		else
		{
			renderPassObject += "\n" + line;
		}
	}

	if ( renderPassObject.length() > 0 )
	{
		renderPasses.push_back(renderPassObject);
	}
}
