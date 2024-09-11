#pragma once
#include "shader.h"
#include "camera.h"
#include "stb_image.h"

// 方向
enum StretchDrection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// 玩家类
class Player {
public:
	/* 外部函数 */
	Player(); // 创建对象
	void Draw(Camera camera); // 绘制对象
	void Stretch(StretchDrection direction); // 拉伸对象
	void Init(); // 重置对象
private:
	/* 内部函数 */
	GLuint loadTexture(char const* path);
	/* 属性 */
	Shader shader;
	GLuint VAO, VBO, EBO;
	GLuint textureAround, textureTop;
	glm::vec3 Position;
	glm::vec3 Offset;
	glm::vec3 scale;
};

