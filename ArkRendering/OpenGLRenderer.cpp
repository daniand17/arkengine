#include "OpenGLRenderer.h"
#include "ShaderLoader.h"

OpenGLRenderer::OpenGLRenderer(ArkWindow * windowHandle)
{
	mWindow = windowHandle->getOSWindowHandle();
}

OpenGLRenderer::OpenGLRenderer() : mShouldRun(true) {}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::InitializeRenderer()
{

}

void OpenGLRenderer::Run()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1, -1, 0,
		1, -1, 0,
		0, 1, 0
	};

	mProgramID = LoadShaders("SimpleVertexShader.vert", "SimpleFragmentShader.frag");

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(mProgramID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*) 0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(mWindow);

		glfwPollEvents();

		mShouldRun = glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS;
	}
	while ( mShouldRun && !glfwWindowShouldClose(mWindow) );
}
