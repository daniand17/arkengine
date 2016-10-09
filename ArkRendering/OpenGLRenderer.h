#pragma once
#include <vector>

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "ArkThread.h"
#include "RenderingGlobals.h"
#include "Vec2.h"
#include "Vec3.h"

enum BufferTypes
{
	ArrayBuffer,
	ElementArray
};

template<typename T>
class BufferData
{
public:
	BufferData(BufferTypes bufferType) : mBufferType(bufferType) { glGenBuffers(1, &mBufferId); }
	~BufferData();
	void BindBufferForDrawing(unsigned int numInOrder) const;
	void DisableBufferForDrawing(unsigned int numInOrder) { glDisableVertexAttribArray(numInOrder); }
	void SetBufferData(std::vector<T> & data);
	GLsizei Size() const { return mSize; }

private:
	GLuint mBufferId;
	GLuint mBufferType;
	GLsizei mSize;
};

template<typename T>
inline BufferData<T>::~BufferData()
{
	glDeleteBuffers(1, &mBufferId);
}

template<typename T>
inline void BufferData<T>::BindBufferForDrawing(unsigned int numInOrder) const
{
	glEnableVertexAttribArray(numInOrder);
	glBindBuffer(mBufferType == ArrayBuffer ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, mBufferId);
	glVertexAttribPointer(
		numInOrder,
		sizeof(T) / 4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void *) 0
	);
}

template<typename T>
inline void BufferData<T>::SetBufferData(std::vector<T> & data) 
{
	GLenum bufType = mBufferType == ArrayBuffer ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
	glBindBuffer(bufType, mBufferId);
	mSize = (sizeof(T)) * data.size();
	glBufferData(bufType, mSize, &data[0], GL_STATIC_DRAW);
}

#ifdef USE_OPENGL
class OpenGLRenderer
{
public:
	static OpenGLRenderer const * Instance() { return mInstance; }
	ArkWindow const * GetWindowHandle() const { return mWindow; }
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer();
	~OpenGLRenderer();
	void Stop() { mShouldRun = false; }
	void DeinitRenderer();
	void InitializeRenderer();
	void Run();

private:
	static OpenGLRenderer * mInstance;
	ArkWindow *	mWindow;
	bool	mShouldRun;
	GLuint	mVertexBufferId;
	GLuint	mVertexArrayId;

	ArkRendering::ShaderProgram	* mShaderProgram;
	BufferData<Vec3> mVertexBuffer;
	BufferData<Vec2> mUvBuffer;
	BufferData<Vec3> mNormalBuffer;
	size_t mNumVerts;
	GLuint mUvBufferId;
	GLuint mNormalBufferId;

private:
};
#endif

