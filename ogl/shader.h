#pragma once

#include <GL/glew.h>
#include <iostream>

class Shader
{
private:

private:
	std::string m_filePath;
	unsigned int m_rendererId;
	unsigned int m_type;
	unsigned int GetUniformLocation(const std::string& name);
	GLuint CompileShader(, std::string& shader);

public:
	Shader(unsigned int type, const std::string& filepath);
	~Shader();
	
	void Bind() const;
	void Unbind() const;
	
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

};