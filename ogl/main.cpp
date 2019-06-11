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
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	
	GLErrorWrapper(glEnable(GL_BLEND));
	GLErrorWrapper(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	VertexArray * vao = new VertexArray();

	VertexBuffer * vb = new VertexBuffer(pos, 4 * 4 * sizeof(float));
	IndexBuffer * ib = new IndexBuffer(indices, 6);

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

	VertexBufferLayout * vbl = new VertexBufferLayout();

	vbl->Push<float>(2);
	vbl->Push<float>(2);

	vao->AddBuffer(*vb, *vbl);

	Shader * sh = new Shader("lol.shader");
	unsigned int location = sh->GetUniformLocation("u_texture");
	sh->SetUniform1f(location, 0);

	Texture * tex = new Texture("kbit.png");
	tex->Bind();

	vb->Unbind();
	ib->Unbind();
	vao->Unbind();
	GLErrorWrapper(glUseProgram(NULL));

	const auto r = Renderer();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		{
			/* Render here */
			r.Clear();
			r.Draw(vao, ib, sh);

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