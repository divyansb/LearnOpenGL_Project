#pragma once
#ifndef  DB_GL
#define  DB_GL

#include <glad/glad.h>
#include <glfw3.h>
#include "file_IO.h"

#define NUM_UNIQUE_VERTS 4
#define NUM_TOTAL_VERTS 6

extern float vertices[NUM_UNIQUE_VERTS * 3];
extern unsigned int indices[NUM_TOTAL_VERTS];

enum class ShaderType
{
	ST_VERTEX,
	ST_FRAGMENT
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void ProcessInput(GLFWwindow *window);

bool InitializeGLFW();

GLFWwindow* GetWindow(const int width, const int height, const char* title);

inline void BufferObjectsSetup(unsigned int &vao, unsigned int &vbo, unsigned int &ebo);

bool OpenGLSetup(GLFWwindow *window, unsigned int &vao, unsigned int &vbo, unsigned int &ebo);

inline bool CompileShader(unsigned int &shader);

bool CreateShader(unsigned int &shader, const ShaderType shaderType, const char *shaderFile);

bool UseShaderProgram(unsigned int &shaderProgram, unsigned int &vertexShader, unsigned int &fragmentShader);

void GLCleanup(unsigned int &vao, unsigned int &vbo, unsigned int &ebo);

bool InitializeGLAD();

#endif // ! DB_GL
