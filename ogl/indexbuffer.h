#pragma once

class IndexBuffer 
{

private:
	unsigned int m_rendererId;
	unsigned int m_count;

public:
	IndexBuffer(void * data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	unsigned int GetCount();
};