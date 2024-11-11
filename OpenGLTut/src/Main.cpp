#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Setting up the variable for the dimensions of the screen
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

// Whenever the window size changes (by OS or by the user) this callback function gets called
static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Process all input
static void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// A function to create a shader, not matter what type
static unsigned int createShader(std::string& source, unsigned int shaderType) {
	// Shader creation
	unsigned int shader = glCreateShader(shaderType);
	// Convert the standart string to const char* (c style string)
	const char* src = source.c_str();

	// Compile the shader
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// Print any error if the compilation fails
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cerr << infoLog << std::endl;
		glDeleteShader(shader);
	}

	return shader;
}

// A function to create a program with a vertex and a fragment shader
static unsigned int createProgram(std::string& vertexShader, std::string& fragmentShader) {
	// Program creation
	unsigned int shaderProgram = glCreateProgram();

	// Creating the two shaders
	unsigned int VS = createShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int FS = createShader(fragmentShader, GL_FRAGMENT_SHADER);

	//Attaching the shaders to the progtam
	glAttachShader(shaderProgram, VS);
	glAttachShader(shaderProgram, FS);

	// Linking the program
	glLinkProgram(shaderProgram);

	// Deleting the shaders (we don't need tghem anymore)
	glDeleteShader(VS);
	glDeleteShader(FS);

	return shaderProgram;
}

// A function that loads a shader from a file
std::string loadShader(const std::string filePath) {
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "Faile to open shader file: " << filePath << std::endl;
		return "";
	}

	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

int main() {
	// Initialize and configure GLFW
	glfwInit();

	// Set hints for the version and the core profile to the current context of GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Window creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Wow, a window.", NULL, NULL);

	// Check if the window is created
	if (window == NULL) {
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Asign the created window to the current context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialize Glad (load all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	float vertices[9] = {
		-0.5f, -0.5f, 0.f,
		 0.5f, -0.5f, 0.f,
		  0.f,  0.5f, 0.f
	};

	// Creattes and binds a vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Creates and binds a vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
	glEnableVertexAttribArray(0);

	std::string vertexShader = loadShader("shaders/Default.vert");
	std::string fragmentShader = loadShader("shaders/Default.frag");

	unsigned int shaderProgram = createProgram(vertexShader, fragmentShader);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Setting the shader program (which one to use)
		glUseProgram(shaderProgram);
		// Drawing the triangles
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete the shader program
	glDeleteProgram(shaderProgram);

	//Terminate GLFW
	glfwTerminate();
	return 0;
}