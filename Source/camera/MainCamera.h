#ifndef CAMERA_H
#define CAMERA_H
#include "../cgpch.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 20.0f;
const float ZOOM = 45.0f;
const float YPOSITION = 1.5f;

enum Camera_Movement
{
     FORWARD,
     BACKWARD,
     LEFT,
     RIGHT
};

class MainCamera
{
public:
     glm::vec3 getCameraPos() const;
     glm::vec3 getCameraForward() const;
     void handle_input(GLFWwindow *window, float dt);
     void debug_UI();
     float get_fov() const;
     float get_near() const;
     float get_far() const;
     glm::mat4 getViewMatrix() const;
     glm::mat4 getPerspectiveMatrix() const;
     MainCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
     ~MainCamera();
private:
     void handle_mouse(float xMovement, float yMovement, float dt);
     void handle_keyboard(Camera_Movement movement, float dt);
     float lastX = 400;
     float lastY = 300;
     float pitch = PITCH;
     float yaw = YAW;
     float fov = ZOOM;
     bool firstMouse = true;
     glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
     glm::vec3 cameraFwd = glm::vec3(0.0f, 0.0f, -1.0f);
     glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif
