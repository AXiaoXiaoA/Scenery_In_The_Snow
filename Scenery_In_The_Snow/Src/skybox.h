#pragma once
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "vector"

// ��պ���
class SkyBox {
public:
    /* �ⲿ���� */
	SkyBox(); // ������պ�
    void Draw(Camera camera);// ������պ�
    void Change(); // �л���պ�
private:
    /* �ڲ����� */
    GLuint loadCubemap(std::vector<std::string> faces); // ��������
    /* ��պ����� */
    Shader shader;
    GLuint VAO, VBO;
    GLuint cubemapTexture;
};

