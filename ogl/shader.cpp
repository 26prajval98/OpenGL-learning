#include "shader.h"
#include "renderer.h"

#include <fstream>
#include <sstream>

static struct ShaderProgramSource ParseShader(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint CompileShader(unsigned int type, std::string & shader)
{
	GLuint id = glCreateShader(type);
	const char * src = shader.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);

	if (res == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char * message = (char *)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, message);
		std::cout
			<< "Failed to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< "shader"
			<< std::endl;
		std::cout << message << std::endl;
	}

	return id;
}

unsigned int Shader::GetUniformLocation(const std::string & name)
{
	unsigned int location = glGetUniformLocation(m_rendererId, "u_texture");
	ASSERT(location != -1);
	return location;
}

Shader::Shader(const std::string & filepath)
	: m_filePath(filepath)
{
	shader_program = ParseShader(m_filePath);
	GLuint program = glCreateProgram();
	GLint vs = CompileShader(GL_VERTEX_SHADER, shader_program.VertexSource);
	GLint fs = CompileShader(GL_FRAGMENT_SHADER, shader_program.FragmentSource);

	m_rendererId = program;

	glAttachShader(m_rendererId, vs);
	glAttachShader(m_rendererId, fs);
	glLinkProgram(m_rendererId);
	glValidateProgram(m_rendererId);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader()
{
	Unbind();
}

void Shader::Bind() const
{
	GLErrorWrapper(glUseProgram(m_rendererId));
}

void Shader::Unbind() const
{
	GLErrorWrapper(glUseProgram(NULL));
}

void Shader::SetUniform4f(unsigned int location, float v0, float v1, float v2, float v3)
{
	glUniform4f(location, 1.0f, 1.0f, 0.0f, 1.0f);
}

void Shader::SetUniform1f(unsigned int location, float v0)
{
	glUniform1f(location, v0);
}

