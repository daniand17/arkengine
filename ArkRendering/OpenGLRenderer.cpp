#include <glm\gtc\matrix_transform.hpp>
#include <glm\vec3.hpp>

#include "OpenGLRenderer.h"
#include "ArkMath.h"
#include "Camera.h"
#include "ModelLoader.h"
#include "RenderingGlobals.h"

using namespace ArkRendering;
using namespace ArkMath;

OpenGLRenderer * OpenGLRenderer::mInstance = NULL;

OpenGLRenderer::OpenGLRenderer(ArkWindow * windowHandle) 
	: mWindow(windowHandle)
	, mVertexBuffer(BufferTypes::ArrayBuffer)
	, mUvBuffer(BufferTypes::ArrayBuffer)
	, mNormalBuffer(BufferTypes::ArrayBuffer)
{
	if ( !mInstance )
		mInstance = this;
}

OpenGLRenderer::OpenGLRenderer() 
	: mShouldRun(true)
	, mVertexBuffer(BufferTypes::ArrayBuffer)
	, mUvBuffer(BufferTypes::ArrayBuffer)
	, mNormalBuffer(BufferTypes::ArrayBuffer) 
{}

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

	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<unsigned int> indices;

	bool result = ModelLoading::loadOBJ(ArkString("suzanne.obj"), verts, uvs, normals);

	mNumVerts = verts.size();

	mVertexBuffer.SetBufferData(verts);
	mNormalBuffer.SetBufferData(normals);
	mUvBuffer.SetBufferData(uvs);

	/*GLuint elementBufferId;
	glGenBuffers(1, &elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);*/
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	mShaderProgram = new ShaderProgram("SimpleVertexShader.vert", "SimpleFragmentShader.frag");
	mShaderProgram->setTexture(new Texture("./IceCube.bmp"));
}

void bindLight(GLuint posId, GLuint dirId, GLuint colId, GLuint powId, LightInfo const & light)
{
	glUniform3f(posId, light.worldPosition.x, light.worldPosition.y, light.worldPosition.z);
	glUniform3f(dirId, light.direction.x, light.direction.y, light.direction.z);
	glUniform3f(colId, light.color.x, light.color.y, light.color.z);
	glUniform1f(powId, light.lightPower);
}

void OpenGLRenderer::Run()
{
	GLFWwindow * win = mWindow->getOSWindowHandle();

	glEnable(GL_DEPTH_TEST);
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

	GLuint ltWorldPosition = glGetUniformLocation(mShaderProgram->getId(), "lightInfo.eyePosition");
	GLuint ltDirection = glGetUniformLocation(mShaderProgram->getId(), "lightInfo.direction");
	GLuint ltColor = glGetUniformLocation(mShaderProgram->getId(), "lightInfo.color");
	GLuint ltPower = glGetUniformLocation(mShaderProgram->getId(), "lightInfo.power");

	ArkRendering::LightInfo light;
	light.worldPosition = Vec3(3, 0, 3);
	light.direction = Vec3(-1, -1, -1);
	light.color = Vec3(1, 1, 1);
	light.lightPower = 0.5f;

	do
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 )
		{
			//printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

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

		Vec3 worldLightPos = light.worldPosition;
		Vec4 xform(worldLightPos.x, worldLightPos.y, worldLightPos.z, 1.0f);
		xform = viewMat * xform;
		light.worldPosition = Vec3(xform.x, xform.y, xform.z);
		// Binding the light (TODO (AD) eventually extract... )
		bindLight(ltWorldPosition, ltDirection, ltColor, ltPower, light);
		light.worldPosition = worldLightPos;

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