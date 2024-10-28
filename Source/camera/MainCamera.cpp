#include "MainCamera.h"

glm::vec3 MainCamera::getCameraPos() const
{
     return cameraPos;
}

glm::vec3 MainCamera::getCameraForward() const
{
     return cameraFwd;
}

void MainCamera::handle_input(GLFWwindow *window, float dt)
{
     // kb
     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
          handle_keyboard(FORWARD, dt);

     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
          handle_keyboard(BACKWARD, dt);

     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
          handle_keyboard(LEFT, dt);

     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
          handle_keyboard(RIGHT, dt);

     if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
     {
          double xpos, ypos;
          glfwGetCursorPos(window, &xpos, &ypos);
          handle_mouse(xpos, ypos, dt);
          glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
     }
     else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
     {
          firstMouse = true;
          glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     }
}

void MainCamera::debug_UI()
{
     ImGui::TextColored(ImVec4(0.3f, 0.0f, 0.5f, 1.0f),"Camera Position");
     ImGui::Text(glm::to_string(cameraPos).c_str());
     ImGui::Text("Camera view matrix");
     ImGui::Text(glm::to_string(getViewMatrix()).c_str());
     ImGui::Text("Projection matrix");
     ImGui::Text(glm::to_string(getPerspectiveMatrix()).c_str());
}

void MainCamera::handle_mouse(float xMovement, float yMovement, float dt)
{
     if (firstMouse)
     {
          lastX = xMovement;
          lastY = yMovement;
          firstMouse = false;
          return;
     }

     float x = xMovement - lastX;
     float y = lastY - yMovement;
     lastX = xMovement;
     lastY = yMovement;

     float sensitivity = SENSITIVITY * dt;
     x *= sensitivity;
     y *= sensitivity;

     yaw += x;
     pitch += y;
     if (pitch > -YAW)
          pitch = -YAW;
     if (pitch < YAW)
          pitch = YAW;
     glm::vec3 direction;
     direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
     direction.y = sin(glm::radians(pitch));
     direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
     cameraFwd = glm::normalize(direction);
}

void MainCamera::handle_keyboard(Camera_Movement movement, float dt)
{
     float speed = SPEED * dt;
     if (movement == FORWARD)
     {
          cameraPos += speed * cameraFwd;
     }

     if (movement == BACKWARD)
     {
          cameraPos -= speed * cameraFwd;
     }

     if (movement == LEFT)
     {
          cameraPos -= glm::normalize(glm::cross(cameraFwd, cameraUp)) * speed;
     }

     if (movement == RIGHT)
     {
          cameraPos += glm::normalize(glm::cross(cameraFwd, cameraUp)) * speed;
     }
}

float MainCamera::get_fov() const
{
     return fov;
}

glm::mat4 MainCamera::getViewMatrix() const
{
     return glm::lookAt(cameraPos, cameraPos + cameraFwd, cameraUp);
}

glm::mat4 MainCamera::getPerspectiveMatrix() const
{
     return glm::perspective(glm::radians(get_fov()), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

MainCamera::MainCamera(glm::vec3 position)
{
     cameraPos = position;
}

MainCamera::~MainCamera()
{
}

float MainCamera::get_near() const
{
    return 0.1f;
}

float MainCamera::get_far() const
{
    return 1000.0f;
}
