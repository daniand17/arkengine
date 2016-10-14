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

OpenGLRenderer * OpenGLRenderer::mInstance = NULL;

OpenGLRenderer::OpenGLRenderer(ArkWindow * windowHandle)
	: mWindow(windowHandle)
	, mVertexBuffer(BufferTypes::ArrayBuffer)
	, mUvBuffer(BufferTypes::ArrayBuffer)
	, mNormalBuffer(BufferTypes::ArrayBuffer)
	, mNumModelsInLastBuffer(0)
{
	if ( !mInstance )
		mInstance = this;
}

OpenGLRenderer::OpenGLRenderer()
	: mShouldRun(true)
	, mVertexBuffer(BufferTypes::ArrayBuffer)
	, mUvBuffer(BufferTypes::ArrayBuffer)
	, mNormalBuffer(BufferTypes::ArrayBuffer)
{
}

OpenGLRenderer::~OpenGLRenderer() { DeinitRenderer(); }

void OpenGLRenderer::DeinitRenderer()
{
	delete mShaderProgram;
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void OpenGLRenderer::InitializeRenderer()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	mShaderProgram = new ShaderProgram("SimpleVertexShader.vert", "SimpleFragmentShader.frag");
	mShaderProgram->setTexture(new Texture("./IceCube.bmp"));
}

void OpenGLRenderer::Run()
{
	GLFWwindow * win = mWindow->getOSWindowHandle();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	Camera cam(Camera::Perspective, 45.0f, 0.1f, 100.0f, Vec2(0, 0), Vec2(1, 1));
	cam.setPosition(Vec3(3, 3, 3));
	cam.setTarget(Vec3(0, 0, 0));
	float rotY = 0.0f;

	GLuint vId = glGetUniformLocation(mShaderProgram->getId(), "V");
	GLuint mId = glGetUniformLocation(mShaderProgram->getId(), "M");
	GLuint mvpId = glGetUniformLocation(mShaderProgram->getId(), "MVP");
	GLuint normId = glGetUniformLocation(mShaderProgram->getId(), "N");

	LightInfo light;
	light.eyePosition = Vec3(3, 3, 3);
	light.color = Vec3(0.5, 0.5, 0.5);
	light.getUniformLocationsFromShader(mShaderProgram->getId());

	MaterialInfo material;
	material.ambient = Vec3(1, 1, 1);
	material.diffuse = Vec3(1, 1, 1);
	material.specular = Vec3(1, 1, 1);
	material.shininess = 128;
	material.getUniformLocationsFromShader(mShaderProgram->getId());

	do
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 )
		{
			printf("%f ms/frame : %f\n", 1000.0 / double(nbFrames), static_cast<double>(mNumModelsInLastBuffer));
			nbFrames = 0;
			lastTime += 1.0;
		}

		updateBuffers();

		rotY += 0.01f;

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(mShaderProgram->getId());
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
		material.bindMaterialToShader();
		light.eyePosition = worldLightPos;

		// Bind the buffers for drawing
		mVertexBuffer.BindBufferForDrawing(0);
		mUvBuffer.BindBufferForDrawing(1);
		mNormalBuffer.BindBufferForDrawing(2);

		glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer.Size());

		mNormalBuffer.DisableBufferForDrawing(2);
		mUvBuffer.DisableBufferForDrawing(1);
		mVertexBuffer.DisableBufferForDrawing(0);

		glfwSwapBuffers(win);
		glfwPollEvents();
		mShouldRun = glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS;
	}
	while ( mShouldRun && !glfwWindowShouldClose(win) );
}

void OpenGLRenderer::updateBuffers()
{
	RendererModelManager * rendererModelManager = RendererModelManager::Instance();

	if ( rendererModelManager )
	{
		std::vector<ModelInfo> modelInfoList;
		rendererModelManager->GetModelsWithMaterialId(0, modelInfoList);
		size_t numModels = modelInfoList.size();
		if ( numModels > 0 && numModels != mNumModelsInLastBuffer )
		{
			mNumModelsInLastBuffer = numModels;
			MeshFactory * meshFactory = ResourceManager::Instance()->GetMeshFactory();
			if ( meshFactory )
			{
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
					mVertexBuffer.SetBufferData(newVertBuffer);
					mNormalBuffer.SetBufferData(newNormalBuffer);
					mUvBuffer.SetBufferData(newUvBuffer);
				}
			}
		}
	}
}
