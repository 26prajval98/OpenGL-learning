#include "texture.h"
#pragma once


Texture::Texture(const std::string filePath)
	: m_filePath(filePath), m_width(0), m_height(0), m_rendererId(0), m_localBuffer(nullptr), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_BPP, 4);
	//std::cout << m_localBuffer << std::endl;
	GLErrorWrapper(glGenTextures(1, &m_rendererId));
	GLErrorWrapper(glBindTexture(GL_TEXTURE_2D, m_rendererId));

	// Always specify
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLErrorWrapper(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	Unbind();
}

Texture::~Texture()
{
	GLErrorWrapper(glDeleteTextures(1, &m_rendererId));
	GLErrorWrapper(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}

void Texture::Bind(unsigned int slot)
{
	GLErrorWrapper(glActiveTexture(GL_TEXTURE0));
	GLErrorWrapper(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}

void Texture::Unbind(unsigned int slot)
{
	GLErrorWrapper(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_localBuffer)
	{
		stbi_image_free(m_localBuffer);
	}
}
