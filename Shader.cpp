#include "Shader.h"
#include "Shader.h"

const char* read_file(const char* filename)
{

	std::ifstream file(filename);

	if (!file.is_open()) 
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return nullptr;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();

	std::string content = buffer.str();

	size_t length = content.length();
	char* c_string = new char[length + 1];

	errno_t err = strcpy_s(c_string, length + 1, content.c_str());
	if (err != 0) 
	{
		std::cerr << "Error copying string: " << err << std::endl;
		delete[] c_string;
		return nullptr;
	}

	return c_string;

}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	const char* vertexShaderSource = read_file(vertexPath);
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	delete vertexShaderSource;

	int success;
	char infoLog[512];

	glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* fragmentShaderSource = read_file(fragmentPath);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	delete fragmentShaderSource;

	glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& m) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setVec3(const std::string& name, const glm::vec3& v) const
{
	glProgramUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
}
