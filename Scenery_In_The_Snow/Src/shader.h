#pragma once
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ��ɫ����
class Shader {
private:
	GLuint shaderProgram;  	// ��ɫ��id
public:
	const GLchar* ReadShader(const char* filename);	 // ��ȡ��ɫ���ļ�
	Shader(const GLchar* vSourcePath, const GLchar* fSourcePath); // ���캯��
	void use();  // ʹ����ɫ������
	void endUse();  // ����ʹ����ɫ������
	GLint getShaderProgramId();  // ��ȡ��ɫ������
	// uniform���ߺ���
	void setUniform(const GLchar* loc, float value);
	void setUniform(const GLchar* loc, float value1, float value2, float value3);
	void setUniform(const GLchar* loc, float value1, float value2, float value3, float value4);
	void setUniform(const GLchar* loc, glm::mat4 value);
	void setUniform(const GLchar* loc, glm::mat3 value);
	void setUniform(const GLchar* loc, glm::vec2 value);
	void setUniform(const GLchar* loc, glm::vec3 value);
	void setUniform(const GLchar* loc, glm::vec4 value);
	void setUniform(const GLchar* loc, int value);
	void setUniform(const char* name, GLuint value);
	void setUniform(const char* name, bool value);
};