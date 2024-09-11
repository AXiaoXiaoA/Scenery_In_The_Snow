#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

// ����ṹ��
struct Vertex
{
    glm::vec3 Position; // λ��
    glm::vec3 Normal; // ����
    glm::vec2 TexCoords; // ��������
    glm::vec3 Tangent; // ����
    glm::vec3 Bitangent; // ������
    int m_BoneIDs[MAX_BONE_INFLUENCE];  // ����Ӱ��ö���Ĺ�����������
    float m_Weights[MAX_BONE_INFLUENCE]; // ÿ�������Ըö����Ȩ��
};
// ����ṹ��
struct Texture
{
    GLuint id; // ����ID
    std::string type; // ��������
    std::string path; // �����ļ�·��
};

// ������
class Mesh {
public:
    /*  ��������  */
    std::vector<Vertex> vertices; // ��������
    std::vector<GLuint> indices; // ��������
    std::vector<Texture> textures; // ��������
    GLuint VAO; // ������������ID
    /*  ����  */
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures); // ���캯��
    void Draw(Shader shader); // ��Ⱦ����

private:
    /*  ��Ⱦ����  */
    GLuint VBO, EBO;
    /*  ����  */
    void setupMesh(); // ��ʼ��
};