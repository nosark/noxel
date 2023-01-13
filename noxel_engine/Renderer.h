#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <intrin.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_CALL(x) gl_clear_error();\
	x;\
	ASSERT(gl_log_call(#x, __FILE__, __LINE__))


void gl_clear_error();
bool gl_log_call(const char* function, const char* file, int line);

class Renderer {
    //TODO:
};

