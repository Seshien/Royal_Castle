#pragma once
#include <iostream>
#include "glm/glm.hpp"

enum CameraMoveType {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{

public:

    Camera()
    {
        lastX = 400;
        lastY = 300;
        currentX = 400;
        currentY = 300;

        speed = 1.0f;
        yaw = -90.0f;
        pitch = 0.0f;

        first_time = true;

        cameraCoords = glm::vec3(0.0f, 2.0f, 2.0f);
        cameraViewCoords = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraDefUpCoords = glm::vec3(0.0f, 1.0f, 0.0f);
        cameraUpCoords = glm::vec3(0.0f, 1.0f, 0.0f);
        cameraRightCoords = glm::vec3(0.0f, 1.0f, 0.0f);
        UpdateView();
    }

    void ChangePosition(CameraMoveType type, float time)
    {
        float velocity = speed * time;
        if (type == FORWARD)
            cameraCoords += cameraViewCoords * velocity;
        if (type == BACKWARD)
            cameraCoords -= cameraViewCoords * velocity;
        if (type == LEFT)
            cameraCoords -= cameraRightCoords * velocity;
        if (type == RIGHT)
            cameraCoords += cameraRightCoords * velocity;
        if (type == UP)
            cameraCoords += cameraUpCoords * velocity;
        if (type == DOWN)
            cameraCoords -= cameraUpCoords * velocity;
    }

    void ChangeViewPosition(float x, float y)
    {
        if (first_time)
        {
            lastX = x;
            lastY = y;
            first_time = false;
        }
        float xoffset = x - lastX;
        float yoffset = lastY - y;
        lastX = x;
        lastY = y;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraViewCoords = glm::normalize(direction);
        UpdateView();
    }

    void printCoords()
    {
        std::cout << cameraCoords.x << " : " << cameraCoords.y << " : " << cameraCoords.z << std::endl;
        std::cout << cameraViewCoords.x << " : " << cameraViewCoords.y << " : " << cameraViewCoords.z << std::endl;
        std::cout << cameraUpCoords.x << " : " << cameraUpCoords.y << " : " << cameraUpCoords.z << std::endl << std::endl;
    }

    // x,y,z
    glm::vec3 cameraCoords;
    glm::vec3 cameraViewCoords;
    glm::vec3 cameraDefUpCoords;
    glm::vec3 cameraUpCoords;
    glm::vec3 cameraRightCoords;

private:

    void UpdateView()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraViewCoords = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        cameraRightCoords = glm::normalize(glm::cross(cameraViewCoords, cameraDefUpCoords));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        cameraUpCoords = glm::normalize(glm::cross(cameraRightCoords, cameraViewCoords));
    }

    float first_time;
    float lastX, lastY;
    float currentX, currentY;
    const float sensitivity = 0.05f;
    float speed;
    float yaw;
    float pitch;

};