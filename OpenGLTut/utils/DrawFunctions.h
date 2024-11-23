#pragma once

#include <iostream>
#include <Settings.h>
#include <Shader.h>
#include <stb_image.h>
#include <glad/glad.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <Vector2.h>
#include <Vector3.h>

static unsigned int VAO, VBO, EBO;

void InitBuffers();

unsigned int loadTexture(const char* filePath);

void drawClear(Vector3 color, float alpha);

void unloadTexture(unsigned int& texture);

void drawRectangle(Vector2 position, Vector2 size, Vector3 color, Shader& shader);

void drawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Vector3 color, Shader& shader);

void drawTexture(unsigned int& textureIndex, Vector2 position, Vector2 size, Shader& shader);

void deleteBuffers();