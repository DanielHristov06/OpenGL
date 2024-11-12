#pragma once
#include <iostream>

class Shader {
public:
	// The id of the program
	unsigned int programID;

	unsigned int createShader(std::string& source, unsigned int shaderType);

	// Constructor (creates the shader program)
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	// Destructor
	~Shader();

	// Use/activate the shader
	void use();

	// Uniform utility
	void setBoolUniform(const std::string& name, bool value) const;
	void setIntUniform(const std::string& name, int value) const;
	void setFloatUniform(const std::string& name, float value) const;

	void destroy();
};