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
	mSize = static_cast<GLsizei>((sizeof(T)) * data.size());
	glBufferData(bufType, mSize, &data[0], GL_STATIC_DRAW);
}