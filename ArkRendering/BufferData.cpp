#include "BufferData.h"
#include "ResourceManager.h"

BufferCache::BufferCache()
	: mVertexBuffer(BufferTypes::ArrayBuffer)
	, mUVBuffer(BufferTypes::ArrayBuffer)
	, mNormalBuffer(BufferTypes::ArrayBuffer)
{
}
void BufferCache::BindBuffersForDrawing() const
{
	mVertexBuffer.BindBufferForDrawing(0);
	mUVBuffer.BindBufferForDrawing(1);
	mNormalBuffer.BindBufferForDrawing(2);
}

void BufferCache::DisableBuffers() const
{
	mNormalBuffer.DisableBufferForDrawing(2);
	mUVBuffer.DisableBufferForDrawing(1);
	mVertexBuffer.DisableBufferForDrawing(0);
}
