#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLErrorWrapper(x) GLClearError(); x; ASSERT(GLCheckError());
void GLClearError();
bool GLCheckError();
