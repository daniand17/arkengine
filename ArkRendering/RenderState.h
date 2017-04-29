#pragma once
#include "ArkRendering.h"
#include "BufferData.h"
class RenderState
{
public:
	RenderState(ArkRendering::MaterialInfo const * material, BufferSet const * bufferSet) : mBufferSet(bufferSet), m_material(material) {}

	unsigned int Size() const { return mBufferSet->Size(); }
	void BindBuffersForDrawing() const { mBufferSet->BindBuffersForDrawing(); }
	void DisableBuffers() const { mBufferSet->DisableBuffers(); }

	void SetBufferSet(BufferSet const * bufferSet) { mBufferSet = bufferSet; }
	ArkRendering::MaterialInfo const * getMaterial() const { return m_material; }

private:
	BufferSet const * mBufferSet;
	ArkRendering::MaterialInfo const * m_material;
};