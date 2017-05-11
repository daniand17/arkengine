#include <glm\gtc\matrix_transform.hpp>
#include <glm\vec3.hpp>

#include "OpenGLRenderer.h"
#include "ArkMath.h"
#include "Camera.h"
#include "ArkDebug.h"
#include "MaterialResource.h"
#include "LightData.h"


using namespace ArkRendering;
using namespace ArkMath;
using namespace std;

OpenGLRenderer * OpenGLRenderer::sm_instance = NULL;

OpenGLRenderer::OpenGLRenderer(ArkWindow * windowHandle)
	: m_arkWindow(windowHandle)
	, m_shaderFactory(NULL)
{

	sm_instance = this;
	m_shaderFactory = new ShaderFactory();
}



void OpenGLRenderer::shutdownRenderer()
{
	glDeleteVertexArrays(1, &mVertexArrayId);
}



void OpenGLRenderer::initializeRenderer()
{
	Debug::Log("Initializing Renderer");
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}



void OpenGLRenderer::renderScene(std::vector<RendererInfo> & renderers)
{
	GLFWwindow * win = m_arkWindow->getOSWindowHandle();
	////////////////////////////////////////////	This belongs elsewhere.. adhoc right now	////////////////////////////////////////////	
	
	Camera cam(m_arkWindow, Camera::Perspective, 45.0f, 0.1f, 100.0f, Vec2(0, 0), Vec2(1, 1));
	cam.setPosition(Vec3(3, 3, 3));
	cam.setTarget(Vec3(0, 0, 0));
	float rotY = 0.0f;

	LightInfo light;
	light.eyePosition = Vec3(3, 3, 3);
	light.color = Vec3(0.5, 0.5, 0.5);

	////////////////////////////////////////////

	clearScreen();

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	// Do timer
	double currentTime = glfwGetTime();
	nbFrames++;
	if ( currentTime - lastTime >= 1.0 )
	{
		//printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}

	std::vector<MaterialResource *> mats;
	for ( std::vector<MaterialResource *>::const_iterator mIt(mats.begin()) ; mIt != mats.end() ; mIt++ )
	{
		// Render all the render states
		MaterialResource const * material = *mIt;

		std::list<RenderPass *> renderPasses = material->getRenderPasses();
		for ( std::list<RenderPass *>::const_iterator rpIt(renderPasses.begin()) ; rpIt != renderPasses.end() ; rpIt++ )
		{
			RenderPass * renderPass(*rpIt);
			renderPass->useShaderProgramAndBindValues();

			//// Temporary camera stuff ////
			rotY += 0.01f;
			cam.setPosition(Vec3(5 * cos(rotY), 3, 5 * sin(rotY)));
			cam.refreshCamera();	
			////////////////////////////////

			Mat4 modelMat = Mat4::identity();
			Mat4 viewMat = cam.getViewMatrix();
			Mat4 normalMat = ((viewMat * modelMat).inverse()).transpose();
			Mat4 mvpMat = cam.getCameraViewingMatrix() * modelMat;

			GLuint programId = renderPass->getShaderProgramId();
			light.getUniformLocationsFromShader(programId);

			glUniformMatrix4fv(glGetUniformLocation(programId, "M"), 1, GL_FALSE, &modelMat[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(programId, "V"), 1, GL_FALSE, &viewMat[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(programId, "MVP"), 1, GL_FALSE, &mvpMat[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(programId, "N"), 1, GL_FALSE, &normalMat[0][0]);

			// Converting the light to eye pos
			Vec3 worldLightPos = light.eyePosition;
			Vec4 xform(worldLightPos.x, worldLightPos.y, worldLightPos.z, 1.0f);
			xform = viewMat * xform;
			light.eyePosition = Vec3(xform.x, xform.y, xform.z);
			light.bindLightToShader();

			light.eyePosition = worldLightPos;
			//renderState->BindBuffersForDrawing();
			//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(renderState->Size()));
			//renderState->DisableBuffers();
		}

	}


	glfwSwapBuffers(win);
	glfwPollEvents();

	if ( glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS )
	{
		exit(0);
	}
}



void OpenGLRenderer::clearScreen()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}