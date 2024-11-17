#include "DrawFunctions.h"

#include <Settings.h>
#include <glad/glad.h>

void InitBuffers() {
	float vertices[] = {
		// positions		// colors
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f  // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawRectangle(float x, float y, float w, float h, float r, float g, float b) {
	float ndcX1 = (x / Settings::WIDTH) * 2.0f - 1.0f;
	float ndcY1 = 1.0f - (y / Settings::HEIGHT) * 2.0f;
	float ndcX2 = ((x + w) / Settings::WIDTH) * 2.0f - 1.0f;
	float ndcY2 = 1.0f - ((y + h) / Settings::HEIGHT) * 2.0f;

	float norR = r / 255.0f;
	float norG = g / 255.0f;
	float norB = b / 255.0f;

	glBindVertexArray(VAO);

	// Update the vertex data with the new position, size, and color
	float updatedVertices[] = {
		ndcX1, ndcY1, 0.0f, norR, norG, norB,
		ndcX2, ndcY1, 0.0f, norR, norG, norB,
		ndcX2, ndcY2, 0.0f, norR, norG, norB,
		ndcX1, ndcY2, 0.0f, norR, norG, norB
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updatedVertices), updatedVertices);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void drawTriangle(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y, float r, float g, float b) {
	float ndcP1X = (p1X / Settings::WIDTH) * 2.0f - 1.0f;
	float ndsP1Y = 1.0f - (p1Y / Settings::HEIGHT) * 2.0f;
	float ndcP2X = (p2X / Settings::WIDTH) * 2.0f - 1.0f;
	float ndsP2Y = 1.0f - (p2Y / Settings::HEIGHT) * 2.0f;
	float ndcP3X = (p3X / Settings::WIDTH) * 2.0f - 1.0f;
	float ndsP3Y = 1.0f - (p3Y / Settings::HEIGHT) * 2.0f;

	float norR = r / 255.0f;
	float norG = g / 255.0f;
	float norB = b / 255.0f;

	float updatedVertices[] = {
		ndcP1X, ndsP1Y, 0.0f, norR, norG, norB,
		ndcP2X, ndsP2Y, 0.0f, norR, norG, norB,
		ndcP3X, ndsP3Y, 0.0f, norR, norG, norB
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updatedVertices), updatedVertices);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void deleteBuffers() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}