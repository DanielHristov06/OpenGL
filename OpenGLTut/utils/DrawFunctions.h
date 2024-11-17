#pragma once

#include <Vector2.h>
#include <Vector3.h>

static unsigned int VAO, VBO, EBO;

void InitBuffers();

void drawRectangle(Vector2 position, Vector2 size, Vector3 color);

void drawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Vector3 color);

void deleteBuffers();