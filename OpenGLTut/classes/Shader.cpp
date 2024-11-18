#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Shader.h"

unsigned int Shader::createShader(std::string& source, unsigned int shaderType) {
	// Shader creation
	unsigned int shader = glCreateShader(shaderType);
	// Convert the standart string to const char* (c style string)
	const char* src = source.c_str();

	// Compile the shader
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// Print any error if the compilation fails
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cerr << infoLog << std::endl;
		glDeleteShader(shader);
	}

	return shader;
}

Shader::Shader() : programID(0){}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	std::string vCode;
	std::string fCode;

	std::ifstream vs;
	std::ifstream fs;

	try {
		vs.open(vertexShaderPath);
		fs.open(fragmentShaderPath);

		if (!vs.is_open()) {
			throw std::runtime_error("Failed to open the vertex shader");
		}
		if (!fs.is_open()) {
			throw std::runtime_error("Failed to open the fragment shader");
		}

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vs.rdbuf();
		fShaderStream << fs.rdbuf();

		vs.close();
		fs.close();

		vCode = vShaderStream.str();
		fCode = fShaderStream.str();
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't create a program: " << e.what() << std::endl;
	}
	catch (std::string e) {
		std::cerr << "Couldn't create a program: " << e << std::endl;
	}

	unsigned int vertexShader = createShader(vCode, GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShader(fCode, GL_FRAGMENT_SHADER);

	programID = glCreateProgram();

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);

	glValidateProgram(programID);

	glLinkProgram(programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

void Shader::use() {
	glUseProgram(programID);
}

void Shader::setBoolUniform(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setIntUniform(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloatUniform(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setMat4Uniform(const std::string& name, const GLfloat* value) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value);
}

void Shader::destroy() {
	glDeleteProgram(programID);
}