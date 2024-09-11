#pragma once
#include "shader.h"
#include "camera.h"
#include "stb_image.h"

// ����
enum StretchDrection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// �����
class Player {
public:
	/* �ⲿ���� */
	Player(); // ��������
	void Draw(Camera camera); // ���ƶ���
	void Stretch(StretchDrection direction); // �������
	void Init(); // ���ö���
private:
	/* �ڲ����� */
	GLuint loadTexture(char const* path);
	/* ���� */
	Shader shader;
	GLuint VAO, VBO, EBO;
	GLuint textureAround, textureTop;
	glm::vec3 Position;
	glm::vec3 Offset;
	glm::vec3 scale;
};

