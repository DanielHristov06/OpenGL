#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Setting up the variable for the dimensions of the screen
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

// Whenever the window size changes (by OS or by the user) this callback function gets called
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Process all input
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
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

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Terminate GLFW
	glfwTerminate();
	return 0;
}