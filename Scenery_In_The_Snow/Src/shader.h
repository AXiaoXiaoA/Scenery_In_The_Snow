#pragma once
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// 着色器类
class Shader {
private:
	GLuint shaderProgram;  	// 着色器id
public:
	const GLchar* ReadShader(const char* filename);	 // 读取着色器文件
	Shader(const GLchar* vSourcePath, const GLchar* fSourcePath); // 构造函数
	void use();  // 使用着色器程序
	void endUse();  // 结束使用着色器程序
	GLint getShaderProgramId();  // 获取着色器程序
	// uniform工具函数
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