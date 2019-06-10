#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "shader.h"

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

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	
	VertexArray * vao = new VertexArray();

	VertexBuffer * vb = new VertexBuffer(pos, 4 * 2 * sizeof(float));
	IndexBuffer * ib = new IndexBuffer(indices, 6);

	VertexBufferLayout * vbl = new VertexBufferLayout();

	vbl->Push<float>(2);

	vao->AddBuffer(*vb, *vbl);

	ShaderProgramSource source = ParseShader("lol.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	unsigned int location = glGetUniformLocation(shader, "u_color");
	ASSERT(location != -1);


	GLErrorWrapper(glGenVertexArrays(1, NULL));
	vb->Unbind();
	ib->Unbind();
	GLErrorWrapper(glUseProgram(NULL));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			GLErrorWrapper(glUseProgram(shader));

			vao->Bind();

			glUniform4f(location, 1.0f, 1.0f, 0.0f, 1.0f);

			ib->Bind();

			//Either bind here or bind in glDrawElements but not both
			//GLErrorWrapper(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices));

			GLErrorWrapper(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	delete vb;
	delete ib;
	glfwTerminate();
	return 0;
}