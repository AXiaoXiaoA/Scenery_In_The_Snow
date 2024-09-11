#include "camera.h"

/* 摄像机功能 */
// 初始化
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
	// 摄像机属性
	this->Position = position;
	this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->WorldUp = up;
	// 欧拉角
	this->Yaw = yaw;
	this->Pitch = pitch;
	// 相机选项
	this->MovementSpeed = SPEED;
	this->MouseSensitivity = SENSITIVITY;
	this->Zoom = ZOOM;

	this->UpdateCameraVectors();
}
// 返回视图矩阵
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}
// 处理鼠标点击（左键平移）
void Camera::ProcessMousePress(float  xOffset, float yOffset, float deltaTime) {
	float velocity = this->MovementSpeed * deltaTime;
	// 计算水平方向的位移
	glm::vec3 horizontalMovement = this->Right * (xOffset / 10.0f);
	// 只保留水平方向的分量，将垂直方向分量设为0
	horizontalMovement.y = 0.0f;
	this->Position += horizontalMovement;

	// 计算前进方向的位移
	glm::vec3 forwardMovement = this->Front * (yOffset / 10.0f);
	// 只保留前进方向的分量，将垂直方向分量设为0
	forwardMovement.y = 0.0f;
	this->Position += forwardMovement;
}
// 处理鼠标点击（右键复原）
void Camera::ProcessMousePress() {
	this->Position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->Yaw = YAW;
	this->Pitch = PITCH;
	this->MovementSpeed = SPEED;
	this->MouseSensitivity = SENSITIVITY;
	this->Zoom = ZOOM;
	this->UpdateCameraVectors();
}
// 处理鼠标移动（旋转）
void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
	xOffset *= this->MouseSensitivity;
	yOffset *= this->MouseSensitivity;
	this->Yaw += xOffset;
	this->Pitch += yOffset;
	// 确保在俯仰角超出边界时，屏幕不会翻转
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f) {
			this->Pitch = 89.0f;
		}
		if (this->Pitch < -89.0f) {
			this->Pitch = -89.0f;
		}
	}
	// 更新
	this->UpdateCameraVectors();
}
// 处理鼠标滚轮（缩放）
void Camera::ProcessMouseScroll(float yOffset) {
	this->Zoom -= (float)yOffset;
	if (Zoom < 1.0f) {
		Zoom = 1.0f;
	}
	if (Zoom > 45.0f) {
		Zoom = 45.0f;
	}
}
// getter
glm::vec3 Camera::getPosition() {
	return this->Position;
}
glm::vec3 Camera::getFront() {
	return this->Front;
}
glm::vec3  Camera::getUp() {
	return this->Up;
}
float Camera::getYaw() {
	return this->Yaw;
}
float Camera::getPitch() {
	return this->Pitch;
}
float Camera::getZoom() {
	return this->Zoom;
}
/* 内部函数 */
// 计算前向向量
void Camera::UpdateCameraVectors() {
	// 计算新的Front向量
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);
	// 重新计算Right和Up向量
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}