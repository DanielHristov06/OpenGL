#pragma once

#include <Vector2.h>
#include <Vector3.h>

static unsigned int VAO, VBO, EBO;

void InitBuffers();

unsigned int loadTexture(const char* filePath);

void unloadTexture(unsigned int& texture);

void drawRectangle(Vector2 position, Vector2 size, Vector3 color);

void drawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Vector3 color);

void drawTexture(unsigned int& textureIndex, Vector2 position, Vector2 size);

void deleteBuffers();