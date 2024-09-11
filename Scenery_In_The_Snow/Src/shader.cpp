#include "shader.h"

// ��ȡ��ɫ���ļ�
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

// ���캯��
Shader::Shader(const GLchar* vSourcePath, const GLchar* fSourcePath) {
	// ���ļ�·���л�ȡ����/Ƭ����ɫ��
	const char* vShaderSource = ReadShader(vSourcePath);
	const char* fShaderSource = ReadShader(fSourcePath);

	// ����������ɫ��
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);
	glCompileShader(vertexShader);
	//������
	GLint success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "VertexShader program failed to compile. " << infoLog << std::endl;
	}

	// ����ƬԪ��ɫ��
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);
	//������
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "FragmentShader program failed to compile. " << infoLog << std::endl;
	}

	// ������ɫ������
	this->shaderProgram = glCreateProgram();

	// ������ɫ��
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);

	// ���Ӽ��
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader program linking failed. " << infoLog << std::endl;
	}

	// ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// ʹ����ɫ������
void Shader::use() {
	// ʹ����ɫ��
	glUseProgram(this->shaderProgram);
}

// ����ʹ����ɫ������
void Shader::endUse()
{
	glUseProgram(0);
}

// ��ȡ��ɫ������
GLint Shader::getShaderProgramId() {
	return this->shaderProgram;
}

// uniform���ߺ���
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