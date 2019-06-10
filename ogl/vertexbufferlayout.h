#pragma once

#include <GL/glew.h>
#include <vector>

struct vb_element
{
	unsigned int type;
	unsigned int count;
};

class VertexBufferLayout
{

private:
	std::vector<vb_element> m_elements;
	unsigned int m_stride;

public:
	VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count });
		m_stride += sizeof(GLfloat) * count;
	}

	inline std::vector<vb_element> GetElements() const { return m_elements; };
	inline unsigned int GetStride() const { return m_stride; };
};