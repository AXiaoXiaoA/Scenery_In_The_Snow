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

// ģ����
class Model
{
public:
    /* �ⲿ���� */
    Model(const GLchar* path);  // ����ģ��
    void Draw(Shader shader); // ����ģ��

private:
    /* ģ������ */
    std::vector<Mesh> meshes; // �洢ģ�͵���������
    std::string directory; // �洢ģ���ļ����ڵ�Ŀ¼·��
    std::vector<Texture> textures_loaded;

    /* �ڲ����� */
    void loadModel(std::string path); // ����ģ��
    void processNode(aiNode* node, const aiScene* scene); // ����ģ�ͽڵ�
    Mesh processMesh(aiMesh* mesh, const aiScene* scene); // ����������
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName); // ���ز�������
    GLint TextureFromFile(const char* path, std::string directory);// ���ļ�·����������
};
