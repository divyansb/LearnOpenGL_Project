#include <iostream>
#include "file_IO.h"
#include "_gl.h"

int main()
{
	InitializeGLFW();
	GLFWwindow *window = GetWindow(800, 800, "Learn OpenGL");
	if (!window)
		return -1;
	if (!InitializeGLAD())
		return -1;

	unsigned int vao, vbo, ebo; 

	OpenGLSetup(window,vao, vbo, ebo); 

	// Vertex shader creation
	unsigned int vertexShader;
	CreateShader(vertexShader, ShaderType::ST_VERTEX, "Shaders/vertexShader_1.txt");
	// Fragment shader compilation
	unsigned int fragmentShader;
	CreateShader(fragmentShader, ShaderType::ST_FRAGMENT, "Shaders/fragmentShader_1.txt");
	// Creating a shader program object
	unsigned int shaderProgram;
	UseShaderProgram(shaderProgram, vertexShader, fragmentShader);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	GLCleanup(vao, vbo, ebo);

	return 0;
}