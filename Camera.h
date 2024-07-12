#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>



enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;



class Camera
{
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	float yaw;
	float pitch;

	float movement_speed;
	float mouse_sensitivity;
	float zoom;

	 Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		 float yaw = YAW, float pitch = PITCH) :
		 front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
    {
        this->position = position;
        this->world_up = up;
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

	 Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
		 front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
	 {
		 this->position = glm::vec3(posX, posY, posZ);
		 this->world_up = glm::vec3(upX, upY, upZ);
		 this->yaw = yaw;
		 this->pitch = pitch;
		 updateCameraVectors();
	 }


	 glm::mat4 getViewMatrix()
	 {
		 return (glm::mat4(right.x, right.y, right.z, 0.0f, up.x, up.y, up.z, 0.0f, front.x, front.y, front.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f) *
			 glm::mat4(1.0f, 0.0f, 0.0f, -position.x, 0.0f, 1.0f, 0.0f, -position.y, 0.0f, 0.0f, 1.0f, -position.z, 0.0f, 0.0f, 0.0f, 1.0f));
		 return glm::lookAt(position, position + front, up);
	 }

	 void processKeyboard(Camera_Movement direction, float deltaTime)
	 {
		 float velocity = movement_speed * deltaTime;
		 if (direction == FORWARD)
			 position += front * velocity;
		 if (direction == BACKWARD)
			 position -= front * velocity;
		 if (direction == LEFT)
			 position -= right * velocity;
		 if (direction == RIGHT)
			 position += right * velocity;
	 }

	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= mouse_sensitivity;
        yoffset *= mouse_sensitivity;

        yaw   += xoffset;
        pitch -= yoffset;

        if (constrainPitch)
        {
            if (pitch > 89.0f)
				pitch = 89.0f;
            if (pitch < -89.0f)
				pitch = -89.0f;
        }

        updateCameraVectors();
    }

	void processMouseScroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

private:

	void updateCameraVectors()
	{
		glm::vec3 front_temp;
		front_temp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front_temp.y = sin(glm::radians(pitch));
		front_temp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front_temp);
		right = glm::normalize(glm::cross(front, world_up)); 
		up = glm::normalize(glm::cross(right, front));
	}

};

#endif