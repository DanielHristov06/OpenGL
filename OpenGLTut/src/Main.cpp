#include <Settings.h>
#include <Shader.h>
#include <DrawFunctions.h>
#include <OtherFunctions.h>

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

	InitBuffers();

	unsigned int index = loadTexture("textures/awesomeface.png");

	Shader shader("shaders/Default.vert", "shaders/Default.frag");
	Shader texShader("shaders/Texture.vert", "shaders/Texture.frag");

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
		drawRectangle(Vector2(32, 32), Vector2(100, 50), Vector3(255, 0, 0));
		drawTriangle(Vector2(640, 64), Vector2(64, 600), Vector2(1280 - 64, 600), Vector3(0, 0, 255));

		texShader.use();
		drawTexture(index, Vector2(320, 32), Vector2(100, 100));

		// Swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	unloadTexture(index);
	deleteBuffers();

	//Terminate GLFW
	glfwTerminate();
	return 0;
}