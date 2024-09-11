#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Ĭ���������ֵ
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// �������
class Camera {
public:
    /* ��������� */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH); // ��ʼ��
    glm::mat4 GetViewMatrix(); // ������ͼ����
	void ProcessMousePress(float  xOffset, float yOffset, float deltaTime); // ��������������ƽ�ƣ�
    void ProcessMousePress(); // ������������Ҽ���ԭ��
    void ProcessMouseMovement(float  xOffset, float yOffset, GLboolean constrainPitch = true); // ��������ƶ�����ת��
    void ProcessMouseScroll(float yOffset); // �������������ţ�
    /* getter&setter */
    glm::vec3 getPosition();
    glm::vec3 getFront();
    glm::vec3 getUp();
    float getYaw();
    float getPitch();
    float getZoom();
private:
    /* �ڲ����� */
    void UpdateCameraVectors(); // ����ǰ������
    /* �������Ϣ */
    // ���������
    glm::vec3 Position; // �����λ��
    glm::vec3 Front; // ��������Եķ�������
    glm::vec3 Up; // ������Ϸ�������
    glm::vec3 Right; // ������ҷ�������
    glm::vec3 WorldUp; // ��������ϵ�е��Ϸ���
    // ŷ���ǣ���ʾ������ķ���
    float Yaw;
    float Pitch;
    // ��������ܲ���
    float MovementSpeed; // ������ƶ��ٶ�
    float MouseSensitivity; // ���������
    float Zoom; // ����ֵ��ͨ�����ڿ����ӳ���ͶӰ��������ţ�
};

