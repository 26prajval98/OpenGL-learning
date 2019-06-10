#pragma once

class VertexBuffer 
{

private:
	unsigned int m_rendererId;

public:
	VertexBuffer(void * data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};