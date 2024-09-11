#pragma once
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "vector"

// 天空盒类
class SkyBox {
public:
    /* 外部函数 */
	SkyBox(); // 创建天空盒
    void Draw(Camera camera);// 绘制天空盒
    void Change(); // 切换天空盒
private:
    /* 内部函数 */
    GLuint loadCubemap(std::vector<std::string> faces); // 加载纹理
    /* 天空盒属性 */
    Shader shader;
    GLuint VAO, VBO;
    GLuint cubemapTexture;
};

