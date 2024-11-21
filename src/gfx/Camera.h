//
// Created by kgil2 on 9/12/2024.
//

#ifndef GLFW2_CAMERA_H
#define GLFW2_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
    const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 position;
    glm::vec3 direction;

    bool firstMouse = true;

    double speed;
    double sensitivity;
    double fov;
    double yaw{ 0 };
    double pitch{ 0 };
    float lastX, lastY;

    void updateVectors();
public:
    Camera(glm::vec3 initPos, glm::vec3 initDir, double speed, double sensitivity, double fov);

    void camMoveKeyCallback(GLFWwindow* window, double deltaTime);
    void cursorMoveCallback(double xpos, double ypos, double deltaTime);

    glm::mat4 calculateViewMat();
};


#endif //GLFW2_CAMERA_H
