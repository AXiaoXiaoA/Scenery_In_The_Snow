#include "shader.h"

// 读取着色器文件
const GLchar* Shader::ReadShader(const char* filename)
{
	FILE* infile = NULL;
	fopen_s(&infile, filename, "rb");
	if (!infile) {
		std::cerr << "Unable to open file '" << filename << "'" << std::endl;
		return NULL;
	}
	fseek(infile, 0, SEEK_END);
	size_t len = ftell(infile);
	fseek(infile, 0, SEEK_SET);
	GLchar* source = new GLchar[len + 1];
	fread(source, 1, len, infile);
	fclose(infile);
	source[len] = '\0';
	return const_cast<const GLchar*>(source);
}

// 构造函数
Shader::Shader(const GLchar* vSourcePath, const GLchar* fSourcePath) {
	// 从文件路径中获取顶点/片段着色器
	const char* vShaderSource = ReadShader(vSourcePath);
	const char* fShaderSource = ReadShader(fSourcePath);

	// 创建顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);
	glCompileShader(vertexShader);
	//编译检查
	GLint success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "VertexShader program failed to compile. " << infoLog << std::endl;
	}

	// 创建片元着色器
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);
	//编译检查
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "FragmentShader program failed to compile. " << infoLog << std::endl;
	}

	// 创建着色器程序
	this->shaderProgram = glCreateProgram();

	// 链接着色器
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);

	// 链接检查
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader program linking failed. " << infoLog << std::endl;
	}

	// 删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// 使用着色器程序
void Shader::use() {
	// 使用着色器
	glUseProgram(this->shaderProgram);
}

// 结束使用着色器程序
void Shader::endUse()
{
	glUseProgram(0);
}

// 获取着色器程序
GLint Shader::getShaderProgramId() {
	return this->shaderProgram;
}

// uniform工具函数
void Shader::setUniform(const GLchar* loc, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, loc), value);
}
void Shader::setUniform(const GLchar* loc, float value1, float value2, float value3) {
	glUniform3f(glGetUniformLocation(shaderProgram, loc), value1, value2, value3);
}
void Shader::setUniform(const GLchar* loc, float value1, float value2, float value3, float value4) {
	glUniform4f(glGetUniformLocation(shaderProgram, loc), value1, value2, value3, value4);
}
void Shader::setUniform(const GLchar* loc, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, loc), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setUniform(const GLchar* loc, glm::mat3 value) {
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, loc), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setUniform(const GLchar* loc, glm::vec2 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, loc), 1, glm::value_ptr(value));
}
void Shader::setUniform(const GLchar* loc, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, loc), 1, glm::value_ptr(value));
}
void Shader::setUniform(const GLchar* loc, glm::vec4 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, loc), 1, glm::value_ptr(value));
}
void Shader::setUniform(const GLchar* loc, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, loc), value);
}
void Shader::setUniform(const char* loc, GLuint value) {
	glUniform1ui(glGetUniformLocation(shaderProgram, loc), value);
}
void Shader::setUniform(const char* loc, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgram, loc), value);
}