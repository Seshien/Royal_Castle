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

	Camera();

	void ChangePosition(CameraMoveType type, float time);

	void ChangeViewPosition(float x, float y);

	void IncreaseSpeed();
	void DecreaseSpeed();
	void ResetSpeed();
    void SetFastSpeed();

	void printCoords();

    // x,y,z
    glm::vec3 cameraCoords;
    glm::vec3 cameraViewCoords;
    glm::vec3 cameraDefUpCoords;
    glm::vec3 cameraUpCoords;
    glm::vec3 cameraRightCoords;

    bool noclip;

private:


	void UpdateView();

    float first_time;
    float lastX, lastY;
    float currentX, currentY;
    const float sensitivity = 0.05f;
    float speed;
    float yaw;
    float pitch;

};