#include "vertexarray.h"
#include "renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
	GLErrorWrapper(glGenVertexArrays(1, &m_rendererId));
	GLErrorWrapper(glBindVertexArray(m_rendererId));
}

VertexArray::~VertexArray()
{
	GLErrorWrapper(glDeleteVertexArrays(1, &m_rendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout & layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.GetStride(), (const void *)(offset*sizeof(float)));
		offset += element.count;
	}
}

void VertexArray::Bind()
{
	GLErrorWrapper(glBindVertexArray(m_rendererId));
}

void VertexArray::Unbind()
{
	GLErrorWrapper(glBindVertexArray(0));
}
