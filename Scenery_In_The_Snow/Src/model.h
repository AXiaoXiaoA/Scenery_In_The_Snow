#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"

#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// 模型类
class Model
{
public:
    /* 外部函数 */
    Model(const GLchar* path);  // 加载模型
    void Draw(Shader shader); // 绘制模型

private:
    /* 模型数据 */
    std::vector<Mesh> meshes; // 存储模型的所有网格
    std::string directory; // 存储模型文件所在的目录路径
    std::vector<Texture> textures_loaded;

    /* 内部函数 */
    void loadModel(std::string path); // 加载模型
    void processNode(aiNode* node, const aiScene* scene); // 处理模型节点
    Mesh processMesh(aiMesh* mesh, const aiScene* scene); // 处理单个网格
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName); // 加载材质纹理
    GLint TextureFromFile(const char* path, std::string directory);// 从文件路径加载纹理
};
