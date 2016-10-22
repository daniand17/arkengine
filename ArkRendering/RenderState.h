#pragma once

#include "ArkRendering.h"
#include "BufferData.h"
class RenderState
{
public:
	RenderState(Resource_Id materialId, BufferSet const * bufferSet) : mBufferSet(bufferSet), mMaterialId(materialId) {}

	Resource_Id GetMaterialId() const { return mMaterialId; }
	size_t Size() const { return mBufferSet->Size(); }
	void BindBuffersForDrawing() const { mBufferSet->BindBuffersForDrawing(); }
	void DisableBuffers() const { mBufferSet->DisableBuffers(); }

	void SetBufferSet(BufferSet const * bufferSet) { mBufferSet = bufferSet; }

private:
	BufferSet const * mBufferSet;
	Resource_Id mMaterialId;
};