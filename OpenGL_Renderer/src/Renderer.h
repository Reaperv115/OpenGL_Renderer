#pragma once
#include <GL/glew.h>

// C++ macros for debugging opengl
#define ASSERT(x) if (!(x)) __debugbreak();
#define Call(x) GetErrors();\
	x;\
	ASSERT(LogCall(#x, __FILE__, __LINE__))

void GetErrors();

bool LogCall(const char* function, const char* file, int line);


class Renderer
{

};
