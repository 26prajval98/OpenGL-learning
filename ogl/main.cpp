#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


GLuint CompileShader(unsigned int type, std::string& shader)
{
	GLuint id = glCreateShader(type);
	const char * src = shader.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);

	if (res)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char * message = (char *)malloc(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, message);

	}

	return id;
}

GLuint CreateShader(std::string& vertex_shader, std::string& fragment_shader)
{
	GLuint program = glCreateProgram();
	GLint vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	GLint fs = CompileShader(GL_VERTEX_SHADER, vertex_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//glDeleteShader(vs);
	//glDeleteShader(fs);

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
		0.0f, 1.0f,
		-1.0f, -1.0f,
		+1.0f, -1.0f,
	};

	GLuint buffer;
	glCreateBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), pos);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}