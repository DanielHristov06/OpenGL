#include "DrawFunctions.h"

void InitBuffers() {
	float vertices[] = {
		// positions		// colors		  // texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // top left
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

unsigned int loadTexture(const char* filePath) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Determine the image format
	std::string fileStr(filePath);
	GLenum format = GL_RGB;

	if (fileStr.substr(fileStr.find_last_of(".") + 1) == "png") format = GL_RGBA;

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		return texture;
	}
	else {
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		stbi_image_free(data);
		return -1;
	}
}

void drawClear(Vector3 color, float alpha) {
	glClearColor(color.x, color.y, color.z, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void unloadTexture(unsigned int& texture) {
	glDeleteTextures(1, &texture);
}

void drawRectangle(Vector2 position, Vector2 size, Vector3 color, Shader& shader) {
	float ndcX1 = (position.x / Settings::WIDTH) * 2.0f - 1.0f;
	float ndcY1 = 1.0f - (position.y / Settings::HEIGHT) * 2.0f;
	float ndcX2 = ((position.x + size.x) / Settings::WIDTH) * 2.0f - 1.0f;
	float ndcY2 = 1.0f - ((position.y + size.y) / Settings::HEIGHT) * 2.0f;

	float norR = color.x / 255.0f;
	float norG = color.y / 255.0f;
	float norB = color.z / 255.0f;

	shader.use();

	glBindVertexArray(VAO);

	// Update the vertex data with the new position, size, and color
	float updatedVertices[] = {
		ndcX1, ndcY1, 0.0f, norR, norG, norB, 1.0f, 1.0f,
		ndcX2, ndcY1, 0.0f, norR, norG, norB, 1.0f, 1.0f,
		ndcX2, ndcY2, 0.0f, norR, norG, norB, 0.0f, 0.0f,
		ndcX1, ndcY2, 0.0f, norR, norG, norB, 0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updatedVertices), updatedVertices);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void drawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Vector3 color, Shader& shader) {
	float ndcP1X = (p1.x / Settings::WIDTH) * 2.0f - 1.0f;
	float ndsP1Y = 1.0f - (p1.y / Settings::HEIGHT) * 2.0f;
	float ndcP2X = (p2.x / Settings::WIDTH) * 2.0f - 1.0f;
	float ndsP2Y = 1.0f - (p2.y / Settings::HEIGHT) * 2.0f;
	float ndcP3X = (p3.x / Settings::WIDTH) * 2.0f - 1.0f;
	float ndsP3Y = 1.0f - (p3.y / Settings::HEIGHT) * 2.0f;

	float norR = color.x / 255.0f;
	float norG = color.y / 255.0f;
	float norB = color.z / 255.0f;

	float updatedVertices[] = {
		ndcP1X, ndsP1Y, 0.0f, norR, norG, norB, 1.0f, 1.0f,
		ndcP2X, ndsP2Y, 0.0f, norR, norG, norB, 1.0f, 1.0f,
		ndcP3X, ndsP3Y, 0.0f, norR, norG, norB, 0.0f, 0.0f
	};

	shader.use();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updatedVertices), updatedVertices);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void drawTexture(unsigned int& textureIndex, Vector2 position, Vector2 size, Shader& shader) {
	float ndcX1 = (position.x / Settings::WIDTH) * 2.0f - 1.0f;
	float ndcY1 = 1.0f - (position.y / Settings::HEIGHT) * 2.0f;
	float ndcX2 = ((position.x + size.x) / Settings::WIDTH) * 2.0f - 1.0f;
	float ndcY2 = 1.0f - ((position.y + size.y) / Settings::HEIGHT) * 2.0f;

	float updatedVertices[] = {
		ndcX1, ndcY1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		ndcX2, ndcY1, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		ndcX2, ndcY2, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		ndcX1, ndcY2, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	shader.use();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updatedVertices), updatedVertices);

	glBindTexture(GL_TEXTURE_2D, textureIndex);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void deleteBuffers() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}