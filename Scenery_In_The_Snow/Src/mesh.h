#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

// 顶点结构体
struct Vertex
{
    glm::vec3 Position; // 位置
    glm::vec3 Normal; // 法线
    glm::vec2 TexCoords; // 纹理坐标
    glm::vec3 Tangent; // 切线
    glm::vec3 Bitangent; // 副法线
    int m_BoneIDs[MAX_BONE_INFLUENCE];  // 骨骼影响该顶点的骨骼索引数组
    float m_Weights[MAX_BONE_INFLUENCE]; // 每个骨骼对该顶点的权重
};
// 纹理结构体
struct Texture
{
    GLuint id; // 纹理ID
    std::string type; // 纹理类型
    std::string path; // 纹理文件路径
};

// 网格类
class Mesh {
public:
    /*  网格数据  */
    std::vector<Vertex> vertices; // 顶点数组
    std::vector<GLuint> indices; // 索引数组
    std::vector<Texture> textures; // 纹理数组
    GLuint VAO; // 顶点数组对象的ID
    /*  函数  */
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures); // 构造函数
    void Draw(Shader shader); // 渲染网格

private:
    /*  渲染数据  */
    GLuint VBO, EBO;
    /*  函数  */
    void setupMesh(); // 初始化
};