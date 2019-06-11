#pragma once

#include <GL/glew.h>
#include <iostream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:

private:
	std::string m_filePath;
	unsigned int m_rendererId;

public:
	ShaderProgramSource shader_program;
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	unsigned int GetUniformLocation(const std::string& name);
	void SetUniform4f(unsigned int location, float v0, float v1, float v2, float v3);
	void SetUniform1f(unsigned int location, float v0);
};