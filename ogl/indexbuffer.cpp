#include "indexbuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(void * data, unsigned int count)
{
	m_count = count;
	glCreateBuffers(1, &m_rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer()
{
	GLErrorWrapper(glDeleteBuffers(1, &m_rendererId));
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void IndexBuffer::Unbind() const
{
	GLErrorWrapper(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));
}

unsigned int IndexBuffer::GetCount()
{
	return m_count;
}
