#include <glm\gtc\matrix_transform.hpp>
#include <glm\vec3.hpp>

#include "OpenGLRenderer.h"
#include "ArkMath.h"
#include "Camera.h"
#include "ModelLoader.h"
#include "RendererModelManager.h"
#include "ArkDebug.h"
#include "ResourceManager.h"

using namespace ArkRendering;
using namespace ArkMath;
using namespace std;
#define DEBUG_MATERIAL_ID 0

OpenGLRenderer * OpenGLRenderer::mInstance = NULL;

OpenGLRenderer::OpenGLRenderer(ArkWindow * windowHandle)
	: mWindow(windowHandle)
{
	if ( !mInstance )
		mInstance = this;
}

OpenGLRenderer::OpenGLRenderer()
	: mShouldRun(true)
{
}

OpenGLRenderer::~OpenGLRenderer() { DeinitRenderer(); }

void OpenGLRenderer::DeinitRenderer()
{
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void OpenGLRenderer::InitializeRenderer()
{
	Debug::Log("Initializing Renderer");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

void OpenGLRenderer::Run()
{
	GLFWwindow * win = mWindow->getOSWindowHandle();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	Camera cam(Camera::Perspective, 45.0f, 0.1f, 100.0f, Vec2(0, 0), Vec2(1, 1));
	cam.setPosition(Vec3(3, 3, 3));
	cam.setTarget(Vec3(0, 0, 0));
	float rotY = 0.0f;

	LightInfo light;
	light.eyePosition = Vec3(3, 3, 3);
	light.color = Vec3(0.5, 0.5, 0.5);

	/*Resource_Id shaderId = ResourceManager::Instance()->GetShaderFactory()->CreateShader("SimpleVertexShader.vert", "SimpleFragmentShader.frag");
	ShaderProgram * program = ResourceManager::Instance()->GetShaderFactory()->GetShaderProgramByResourceId(shaderId);
	program->setTexture(new Texture("./rock_texture.bmp"));
	material->setShaderProgram(program->getId());*/

	MaterialFactory * matFac = ResourceManager::Instance()->GetMaterialFactory();
	MaterialInfo * material = matFac->GetMaterialById(0);
	if ( material )
	{
		ModelInfo * modelInfo = RendererModelManager::Instance()->GetNextModelInfoForPopulate();
		modelInfo->materialId = material->id;
		modelInfo->meshId = ResourceManager::Instance()->GetMeshFactory()->LoadMesh("rock.obj");
		modelInfo->modelMatrix = Mat4::identity();
	}
	

	do
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Do timer
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 )
		{
			printf("%f ms/frame", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		updateBufferSets();

		// Render all the render states
		for ( RenderState * renderState : mRenderStateList )
		{
			MaterialInfo * material = ResourceManager::Instance()->GetMaterialFactory()->GetMaterialById(renderState->GetMaterialId());

			if ( material )
			{
				material->UseShaderProgram();
				GLuint programId = material->GetShaderProgramId();

				GLuint vId = glGetUniformLocation(programId, "V");
				GLuint mId = glGetUniformLocation(programId, "M");
				GLuint mvpId = glGetUniformLocation(programId, "MVP");
				GLuint normId = glGetUniformLocation(programId, "N");

				light.getUniformLocationsFromShader(programId);

				rotY += 0.01f;

				cam.setPosition(Vec3(5 * cos(rotY), 3, 5 * sin(rotY)));
				cam.refreshCamera();	// TODO (AD) perhaps move this to an update loop outside the renderer

				Mat4 modelMat = Mat4::identity();
				Mat4 viewMat = cam.getViewMatrix();
				Mat4 normalMat = ((viewMat * modelMat).inverse()).transpose();
				Mat4 mvpMat = cam.getCameraViewingMatrix() * modelMat;

				glUniformMatrix4fv(mId, 1, GL_FALSE, &modelMat[0][0]);
				glUniformMatrix4fv(vId, 1, GL_FALSE, &viewMat[0][0]);
				glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvpMat[0][0]);
				glUniformMatrix4fv(normId, 1, GL_FALSE, &normalMat[0][0]);

				// Converting the light to eye pos
				Vec3 worldLightPos = light.eyePosition;
				Vec4 xform(worldLightPos.x, worldLightPos.y, worldLightPos.z, 1.0f);
				xform = viewMat * xform;
				light.eyePosition = Vec3(xform.x, xform.y, xform.z);
				light.bindLightToShader();

				light.eyePosition = worldLightPos;
				renderState->BindBuffersForDrawing();
				glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(renderState->Size()));	// TODO failure here
				renderState->DisableBuffers();
			}
		}

		glfwSwapBuffers(win);
		glfwPollEvents();
		mShouldRun = glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS;
	}
	while ( mShouldRun && !glfwWindowShouldClose(win) );
}

void OpenGLRenderer::updateBufferSets()
{
	RendererModelManager * rendererModelManager = RendererModelManager::Instance();

	if ( !rendererModelManager || !rendererModelManager->IsDirty() )
		return;

	MeshFactory * meshFactory = ResourceManager::Instance()->GetMeshFactory();
	if ( !meshFactory ) return;

	std::vector<Resource_Id> usedMaterialIds;
	rendererModelManager->GetUsedMaterialIds(usedMaterialIds);

	for ( vector<Resource_Id>::const_iterator resIdIter = usedMaterialIds.begin() ; resIdIter < usedMaterialIds.end() ; resIdIter++ )
	{
		Resource_Id resourceId = (*resIdIter);
		std::vector<ModelInfo> modelInfoList;
		rendererModelManager->GetModelsWithMaterialId((*resIdIter), modelInfoList);

		BufferSet * currBufferSet = NULL;
		if ( mBufferSetMap.find(resourceId) == mBufferSetMap.end() )
		{
			currBufferSet = new BufferSet();
			mBufferSetMap[resourceId] = currBufferSet;
			mRenderStateList.push_back(new RenderState(resourceId, currBufferSet));
		}
		else
			currBufferSet = mBufferSetMap[resourceId];

		std::vector<Vec3> newVertBuffer;
		std::vector<Vec3> newNormalBuffer;
		std::vector<Vec2> newUvBuffer;
		size_t vertCount = 0;
		size_t normalCount = 0;
		size_t uvCount = 0;
		for ( size_t i = 0 ; i < modelInfoList.size() ; i++ )
		{
			MeshInfo * meshInfo = meshFactory->GetMeshById(modelInfoList[i].meshId);
			if ( meshInfo )
			{
				vertCount += meshInfo->vertices.size();
				normalCount += meshInfo->normals.size();
				uvCount += meshInfo->uvs.size();
			}
		}

		if ( vertCount > 0 )
		{
			newVertBuffer.reserve(vertCount);
			newNormalBuffer.reserve(normalCount);
			newUvBuffer.reserve(uvCount);
			for ( size_t i = 0 ; i < modelInfoList.size() ; i++ )
			{
				MeshInfo * meshInfo = meshFactory->GetMeshById(modelInfoList[i].meshId);
				newVertBuffer.insert(newVertBuffer.end(), meshInfo->vertices.begin(), meshInfo->vertices.end());
				newNormalBuffer.insert(newNormalBuffer.end(), meshInfo->normals.begin(), meshInfo->normals.end());
				newUvBuffer.insert(newUvBuffer.end(), meshInfo->uvs.begin(), meshInfo->uvs.end());
			}
			
			currBufferSet->GetVertexBuffer()->SetBufferData(newVertBuffer);
			currBufferSet->GetNormalBuffer()->SetBufferData(newNormalBuffer);
			currBufferSet->GetUVBuffer()->SetBufferData(newUvBuffer);
		}

		rendererModelManager->SetModelsUpdated();
	}
}
