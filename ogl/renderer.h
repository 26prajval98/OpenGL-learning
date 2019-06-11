#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <iostream>

#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"

#define GLCall GLErrorWrapper
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLErrorWrapper(x) GLClearError(); x; ASSERT(GLCheckError());
void GLClearError();
bool GLCheckError();

class Renderer
{
public:
	void Draw(VertexArray*& vao, IndexBuffer*& ib, Shader*& shader) const;
	void Clear() const;
};