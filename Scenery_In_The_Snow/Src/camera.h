#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// 默认摄像机数值
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// 摄像机类
class Camera {
public:
    /* 摄像机功能 */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH); // 初始化
    glm::mat4 GetViewMatrix(); // 返回视图矩阵
	void ProcessMousePress(float  xOffset, float yOffset, float deltaTime); // 处理鼠标点击（左键平移）
    void ProcessMousePress(); // 处理鼠标点击（右键复原）
    void ProcessMouseMovement(float  xOffset, float yOffset, GLboolean constrainPitch = true); // 处理鼠标移动（旋转）
    void ProcessMouseScroll(float yOffset); // 处理鼠标滚（缩放）
    /* getter&setter */
    glm::vec3 getPosition();
    glm::vec3 getFront();
    glm::vec3 getUp();
    float getYaw();
    float getPitch();
    float getZoom();
private:
    /* 内部函数 */
    void UpdateCameraVectors(); // 计算前向向量
    /* 摄像机信息 */
    // 摄像机属性
    glm::vec3 Position; // 摄像机位置
    glm::vec3 Front; // 摄像机正对的方向向量
    glm::vec3 Up; // 摄像机上方向向量
    glm::vec3 Right; // 摄像机右方向向量
    glm::vec3 WorldUp; // 世界坐标系中的上方向
    // 欧拉角（表示摄像机的方向）
    float Yaw;
    float Pitch;
    // 摄像机性能参数
    float MovementSpeed; // 摄像机移动速度
    float MouseSensitivity; // 鼠标灵敏度
    float Zoom; // 缩放值（通常用于控制视场或投影矩阵的缩放）
};

