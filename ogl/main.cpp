#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLErrorWrapper(x) GLClearError(); x; ASSERT(GLCheckError());

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError()
{
	while (GLenum error = glGetError())
	{

		std::cout << "[OpenGL Error] ";
		switch (error) {
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
			break;
		default:
			std::cout << "Unrecognized error" << error;
		}
		std::cout << std::endl;
		return false;
	}
	return true;
}

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

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


GLuint CompileShader(unsigned int type, std::string& shader)
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

GLuint CreateShader(std::string& vertex_shader, std::string& fragment_shader)
{
	GLuint program = glCreateProgram();
	GLint vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	GLint fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	float pos[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	GLuint buffer;
	glCreateBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), pos, GL_STATIC_DRAW);


	//Either bind here or bind in glDrawElements but not both
	//GLuint index_buffer;							
	//glCreateBuffers(1, &index_buffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	ShaderProgramSource source = ParseShader("lol.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	unsigned int location = glGetUniformLocation(shader, "u_color");
	ASSERT(location != -1);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLintptr)0*sizeof(float));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform4f(location, 1.0f, 1.0f, 0.0f, 1.0f);
		GLErrorWrapper(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices));
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}