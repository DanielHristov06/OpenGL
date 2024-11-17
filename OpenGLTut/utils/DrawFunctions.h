#pragma once

static unsigned int VAO, VBO, EBO;

void InitBuffers();

void drawRectangle(float x, float y, float w, float h, float r, float g, float b);

void drawTriangle(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y, float r, float g, float b);

void deleteBuffers();