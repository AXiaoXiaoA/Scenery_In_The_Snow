#include "skybox.h"

// 创建天空盒
SkyBox::SkyBox() : shader("../Scenery_In_The_Snow/Shader/skybox.vs", "../Scenery_In_The_Snow/Shader/skybox.fs") {
    float vertices[] = {        
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    std::vector<std::string> faces {
        "../Scenery_In_The_Snow/Res/skybox/day/right.png",
        "../Scenery_In_The_Snow/Res/skybox/day/left.png",
        "../Scenery_In_The_Snow/Res/skybox/day/top.png",
        "../Scenery_In_The_Snow/Res/skybox/day/bottom.png",
        "../Scenery_In_The_Snow/Res/skybox/day/front.png",
        "../Scenery_In_The_Snow/Res/skybox/day/back.png",
    };
    this->cubemapTexture = loadCubemap(faces);
}

// 绘制天空盒子
void SkyBox::Draw(Camera camera) {
    glDepthFunc(GL_LEQUAL);
    this->shader.use();
    this->shader.setUniform("skybox", 0);
    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    glm::mat4 projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);
    
    // 昼夜交替
    float t = fmod(glfwGetTime(), 20.0f) / 20.0f;
    glm::vec3 color1 = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 color2 = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 ambientLight;
    if (t < 0.25f) {
        // 前五秒，逐渐变亮
        float transitionT = glm::smoothstep(0.0f, 1.0f, t / 0.25f);
        ambientLight = glm::mix(color2, color1, transitionT);
    }
    else if (t < 0.5f) {
        // 中间五秒，保持一个亮度
        ambientLight = color1;
    }
    else if (t < 0.75f) {
        // 后五秒，逐渐变暗
        float transitionT = glm::smoothstep(0.0f, 1.0f, (t - 0.5f) / 0.25f);
        ambientLight = glm::mix(color1, color2, transitionT);
    }
    else {
        // 最后五秒，保持一个亮度
        ambientLight = color2;
    }
    this->shader.setUniform("ambientLight", ambientLight);

    glBindVertexArray(this->VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

// 切换天空盒
void SkyBox::Change() {

}

// 加载纹理
GLuint SkyBox::loadCubemap(std::vector<std::string> faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < faces.size(); i++) {
        image = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (image) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
        stbi_image_free(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}