#include "_gl.h"

float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


bool InitializeGLFW()
{
	// Set openGL version and the profile to use.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}


GLFWwindow* GetWindow(const int width, const int height, const char* title)
{
	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window";
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	return window;
}


inline void BufferObjectsSetup(unsigned int &vao, unsigned int &vbo, unsigned int &ebo)
{
	// Vertex array object
	// VAO stores the vertex attribute configuration and the vertex buffer data to use it
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex buffer object
	// Generate buffer, bind and copy data to it
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);	// bind vbo to GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element buffer object
	// Index buffer to avoid repeating vertex data in the vertex buffer 
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


bool OpenGLSetup(GLFWwindow *window, unsigned int &vao, unsigned int &vbo, unsigned int &ebo)
{
	// OpenGL viewport size
	glViewport(0, 0, 800, 800);

	// Callback function to be called each time a window is resized
	// Callback functions are to be registered after we have created the window and before the game loop is initiated.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	BufferObjectsSetup(vao, vbo, ebo);

	// Vertex attribute pointer
	// maps the data in the supplied vertex buffer to the input of the vertex shader; 
	// first parameter '0' maps data to the input parameter of the vertex shader 'location' as specified by the 'layout' in the shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return true;
}


inline bool CompileShader(unsigned int &shader)
{
	glCompileShader(shader);
	// Check compile time errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "error: shader failed compilation :" << infoLog << std::endl;
		return false;
	}
	return true;
}


bool CreateShader(unsigned int &shader, const ShaderType shaderType, const char *shaderFile)
{
	switch (shaderType)
	{
	case ShaderType::ST_FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::ST_VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	}

	std::string shaderCode;
	ReadFromFile(shaderFile, shaderCode);
	const char* shaderSource = shaderCode.c_str();

	if (!shaderSource)
		return false;

	glShaderSource(shader, 1, &shaderSource, NULL);
	CompileShader(shader);
	return true;
}


bool UseShaderProgram(unsigned int &shaderProgram, unsigned int &vertexShader, unsigned int &fragmentShader)
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success_link;
	char infolog_link[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_link);
	if (!success_link)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog_link);
		std::cout << "error: program linking failed :" << infolog_link << std::endl;
		return false;
	}
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}


void GLCleanup(unsigned int &vao, unsigned int &vbo, unsigned int &ebo)
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glfwTerminate();
}


bool InitializeGLAD()
{
	// Need to initialize GLAD to be able to call any openGL functions
	// GLAD initialization needs to be after the window has been created and set as the current context and before making calls to any gl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}