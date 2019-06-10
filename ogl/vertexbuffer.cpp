#include "vertexbuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(void * data, unsigned int size)
{
	glCreateBuffers(1, &m_rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	GLErrorWrapper(glDeleteBuffers(1, &m_rendererId));
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void VertexBuffer::Unbind() const
{
	GLErrorWrapper(glBindBuffer(GL_ARRAY_BUFFER, NULL));
}
