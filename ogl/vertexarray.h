#pragma once

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray 
{
private:
	unsigned int m_rendererId;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind();
	void Unbind();
};