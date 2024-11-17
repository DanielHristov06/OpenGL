#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Settings.h>
#include <Shader.h>
#include <DrawFunctions.h>

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
	GLFWwindow* window = glfwCreateWindow(Settings::WIDTH, Settings::HEIGHT, "Wow, a window.", NULL, NULL);

	// Check if the window is created
	if (window == NULL) {
		std::cerr << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Asign the created window to the current context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialize Glad (load all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	InitRectangle();

	Shader shader("shaders/Default.vert", "shaders/Default.frag");

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Setting the shader program (which one to use)
		shader.use();

		// Drawing the triangles
		drawRectangle(32, 32, 100, 50, 255, 0, 0);

		// Swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Terminate GLFW
	deleteRectangle();

	glfwTerminate();
	return 0;
}