#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "skybox.h"
#include "player.h"

#include <iostream>


// 回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, Player& player);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window, Player& player);

// 参数
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// 摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// 渲染
void rend(Shader shader, Model myModel, glm::vec3 translate, glm::vec3 scale) {
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setUniform("projection", projection);
    glm::mat4 view = camera.GetViewMatrix();
    shader.setUniform("view", view);
    shader.setUniform("viewPos", camera.getPosition());

    // 平行光
    float t = fmod(glfwGetTime(), 20.0f) / 20.0f;
    float transitionT = 0.0f;
    if (t < 0.25f) {
        transitionT = t / 0.25f;
    }
    else if (t < 0.5f) {
        transitionT = 1.0f;
    }
    else if (t < 0.75f) {
        transitionT = 1.0f - (t - 0.5f) / 0.25f;
    }
    else {
        transitionT = 0.0f;
    }
    float sunAngle = transitionT * 2.0f * glm::pi<float>();
    glm::vec3 sunDirection = glm::vec3(cos(sunAngle), sin(sunAngle), -0.5f);
    shader.setUniform("myDirectionalLight.direction", sunDirection);
    float ambientIntensity = glm::mix(0.2f, 1.0f, transitionT);
    float diffuseIntensity = glm::mix(0.4f, 1.0f, transitionT);
    float specularIntensity = glm::mix(0.1f, 0.3f, transitionT);
    shader.setUniform("myDirectionalLight.ambient", ambientIntensity, ambientIntensity, ambientIntensity);
    shader.setUniform("myDirectionalLight.diffuse", diffuseIntensity, diffuseIntensity, diffuseIntensity);
    shader.setUniform("myDirectionalLight.specular", specularIntensity, specularIntensity, specularIntensity);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translate);
    model = glm::scale(model, scale);
    shader.setUniform("model", model);
    myModel.Draw(shader);
}

int main()
{
    // 初始化和配置GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建GLFW窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RealSceneInTheSnow", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 加载纹理时翻转图像y轴
    stbi_set_flip_vertically_on_load(false);
    // 开启深度检测
    glEnable(GL_DEPTH_TEST);
    Shader shader("../Scenery_In_The_Snow/Shader/player.vs", "../Scenery_In_The_Snow/Shader/player.fs");
    //创建天空盒与模型
    SkyBox skybox;
    Shader modelShader("../Scenery_In_The_Snow/Shader/model.vs", "../Scenery_In_The_Snow/Shader/model.fs");
    Model sonwmanModel("../Scenery_In_The_Snow/Res/snowman/snowman_finish.obj"); // 创建雪人
    Model houseModel("../Scenery_In_The_Snow/Res/house/6H1.obj"); // 创建房屋
    Model treeModel1("../Scenery_In_The_Snow/Res/tree/Gledista_Triacanthos.obj"); // 创建树木1
    Model treeModel2("../Scenery_In_The_Snow/Res/tree/Gledista_Triacanthos_2.obj"); // 创建树木2
    Player player;

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 每帧时间逻辑
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 处理输入
        processInput(window, player);
        mouse_callback(window, player);

        // 渲染
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rend(modelShader, sonwmanModel, glm::vec3(5.0f, -1.75f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        rend(modelShader, houseModel, glm::vec3(0.0f, -1.75f, -15.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        rend(modelShader, treeModel1, glm::vec3(-10.0f, -1.75f, -25.0f), glm::vec3(0.3f, 0.3f, 0.3f));
        rend(modelShader, treeModel2, glm::vec3(15.0f, -1.75f, -25.0f), glm::vec3(0.3f, 0.3f, 0.3f));
        player.Draw(camera);
        skybox.Draw(camera);

        // 交换缓冲区和处理IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// 调整窗口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
// 监控键盘输入（ctrl键旋转，上下左右键拉伸）
void processInput(GLFWwindow* window, Player& player) {
    // Esc键退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // ctrl键旋转
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
        // 获取鼠标位置
        double xPosIn, yPosIn;
        glfwGetCursorPos(window, &xPosIn, &yPosIn);
        // 坐标类型转换
        float xPos = static_cast<float>(xPosIn);
        float yPos = static_cast<float>(yPosIn);
        // 首次移动处理
        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }
        // 计算偏移量
        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        // 更新上一帧鼠标位置
        lastX = xPos;
        lastY = yPos;
        // 调用摄像机的鼠标移动处理函数
        camera.ProcessMouseMovement(xOffset, yOffset);
    }
    // 上下左右键拉伸
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        player.Stretch(UP);
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        player.Stretch(DOWN);
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        player.Stretch(LEFT);
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        player.Stretch(RIGHT);
    }
}
// 监控鼠标点击（左键平移，右键复原）
void mouse_callback(GLFWwindow* window, Player& player) {
    // 左键平移
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // 获取鼠标位置
        double xPosIn, yPosIn;
        glfwGetCursorPos(window, &xPosIn, &yPosIn);
        // 坐标类型转换
        float xPos = static_cast<float>(xPosIn);
        float yPos = static_cast<float>(yPosIn);
        // 首次移动处理
        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }
        // 计算偏移量
        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        // 更新上一帧鼠标位置
        lastX = xPos;
        lastY = yPos;
        // 调用摄像机的鼠标点击处理函数
        camera.ProcessMousePress(xOffset, yOffset, deltaTime);
    }
    // 右键复原
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera.ProcessMousePress();
        player.Init();
    }
}
// 监控鼠标滚轮（缩放）
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}