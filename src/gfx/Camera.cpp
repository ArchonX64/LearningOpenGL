//
// Created by kgil2 on 9/12/2024.
//

#include "Camera.h"

Camera::Camera(glm::vec3 initPos, glm::vec3 initDir, double speed, double sensitivity, double fov)
    : position(initPos), direction(initDir), speed(speed), sensitivity(sensitivity), fov(fov){}


void Camera::camMoveKeyCallback(GLFWwindow *window, double deltaTime) {
    float timeSpeed = speed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * timeSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * timeSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::normalize(glm::cross(direction, worldUp)) * timeSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= glm::normalize(glm::cross(direction, worldUp)) * timeSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += worldUp * timeSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= worldUp * timeSpeed;
    }
}

void Camera::cursorMoveCallback(double xpos, double ypos, double deltaTime) {
    float timeSens = sensitivity * deltaTime;

    if(firstMouse) {
        lastX = 400, lastY = 300;
        firstMouse = false;
    }

    float xOff = xpos - lastX;
    float yOff = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    yaw += xOff * timeSens;
    pitch += yOff * timeSens;

    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;
}

glm::mat4 Camera::calculateViewMat() {
    glm::vec3 newDir;
    newDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newDir.y = sin(glm::radians(pitch));
    newDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(newDir);
    return glm::lookAt(position, position + direction, worldUp);
}