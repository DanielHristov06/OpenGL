#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Whenever the window size changes (by OS or by the user) this callback function gets called
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Process all input
void processInput(GLFWwindow* window);