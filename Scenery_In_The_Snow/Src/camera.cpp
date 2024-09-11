#include "camera.h"

/* ��������� */
// ��ʼ��
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
	// ���������
	this->Position = position;
	this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->WorldUp = up;
	// ŷ����
	this->Yaw = yaw;
	this->Pitch = pitch;
	// ���ѡ��
	this->MovementSpeed = SPEED;
	this->MouseSensitivity = SENSITIVITY;
	this->Zoom = ZOOM;

	this->UpdateCameraVectors();
}
// ������ͼ����
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}
// ��������������ƽ�ƣ�
void Camera::ProcessMousePress(float  xOffset, float yOffset, float deltaTime) {
	float velocity = this->MovementSpeed * deltaTime;
	// ����ˮƽ�����λ��
	glm::vec3 horizontalMovement = this->Right * (xOffset / 10.0f);
	// ֻ����ˮƽ����ķ���������ֱ���������Ϊ0
	horizontalMovement.y = 0.0f;
	this->Position += horizontalMovement;

	// ����ǰ�������λ��
	glm::vec3 forwardMovement = this->Front * (yOffset / 10.0f);
	// ֻ����ǰ������ķ���������ֱ���������Ϊ0
	forwardMovement.y = 0.0f;
	this->Position += forwardMovement;
}
// ������������Ҽ���ԭ��
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
// ��������ƶ�����ת��
void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
	xOffset *= this->MouseSensitivity;
	yOffset *= this->MouseSensitivity;
	this->Yaw += xOffset;
	this->Pitch += yOffset;
	// ȷ���ڸ����ǳ����߽�ʱ����Ļ���ᷭת
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f) {
			this->Pitch = 89.0f;
		}
		if (this->Pitch < -89.0f) {
			this->Pitch = -89.0f;
		}
	}
	// ����
	this->UpdateCameraVectors();
}
// ���������֣����ţ�
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
/* �ڲ����� */
// ����ǰ������
void Camera::UpdateCameraVectors() {
	// �����µ�Front����
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);
	// ���¼���Right��Up����
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}