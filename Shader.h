#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



const char* read_file(const char* filename);

class Shader
{
public:

	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4& m) const;
	void setVec3(const std::string& name, const glm::vec3& v) const;

};

#endif