#pragma once

#include "renderer.h"
#include "stb_image.h"

class Texture
{
public:
	Texture(const std::string m_filePath);
	~Texture();

private:
	unsigned int m_rendererId;
	std::string m_filePath;
	unsigned char * m_localBuffer;
	int m_width, m_height, m_BPP;

public :
	void Bind(unsigned int slot = 0);
	void Unbind(unsigned int slot = 0);
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};