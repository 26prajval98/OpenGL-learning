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

	Shader * sh = new Shader("lol.shader");
	unsigned int location = sh->GetUniformLocation("u_color");

	vb->Unbind();
	ib->Unbind();
	vao->Unbind();
	GLErrorWrapper(glUseProgram(NULL));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);


			vao->Bind();

			sh->Bind();
			sh->SetUniform4f(location, 1.0f, 1.0f, 0.0f, 1.0f);

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

	delete sh;
	delete vb;
	delete ib;
	glfwTerminate();
	return 0;
}