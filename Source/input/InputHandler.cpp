#include "InputHandler.h"

InputHandler::InputHandler(GLFWwindow *window)
{
     this->window = window;
     glfwSetWindowUserPointer(window, this);
     glfwSetKeyCallback(window, keyCallback);
     glfwSetMouseButtonCallback(window, mouseButtonCallback);
     glfwSetScrollCallback(window, mouseScrollCallback);
     glfwSetDropCallback(window, fileDropCallback);
     glfwSetCursorPosCallback(window, mouseMoveCallback);
     CG_CORE_INFO("Input handler initalized");
}

InputHandler::~InputHandler()
{
     glfwSetKeyCallback(window, nullptr);
     glfwSetMouseButtonCallback(window, nullptr);
     glfwSetScrollCallback(window, nullptr);
     glfwSetDropCallback(window, nullptr);
     glfwSetWindowUserPointer(window, nullptr);
     window = nullptr;
     CG_CORE_INFO("Cleaned up input handler");
}

void InputHandler::addKeyListener(const std::function<void(GLFWwindow *, int, int, int, int)> &listener)
{
     keyListeners.push_back(listener);
}

void InputHandler::addMouseButtonListener(const std::function<void(GLFWwindow *, int, int, int)> &listener)
{
     mouseButtonListeners.push_back(listener);
}

void InputHandler::addMouseScrollListener(const std::function<void(GLFWwindow *, int, int)> &listener)
{
     scrollListeners.push_back(listener);
}

void InputHandler::addFileDropListener(const std::function<void(GLFWwindow *, int, const char **)> &listener)
{
     fileDropListeners.push_back(listener);
}

void InputHandler::addMouseMoveListener(const std::function<void(GLFWwindow *, double, double)> &listener)
{
     moveListeners.push_back(listener);
}

void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
     InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
     if(!handler)
     {
          return;
     }

     for(const auto &listener : handler->keyListeners)
     {
          listener(window, key, scancode, action, mods);
     }
}

void InputHandler::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
     InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
     if(!handler)
     {
          return;
     }

     for(const auto &listener : handler->mouseButtonListeners)
     {
          listener(window, button, action, mods);
     }
}

void InputHandler::mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
     InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
     if(!handler)
     {
          return;
     }

     for(const auto &listener : handler->scrollListeners)
     {
          listener(window, xoffset, yoffset);
     }
}

void InputHandler::fileDropCallback(GLFWwindow *window, int count, const char **paths)
{
     InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
     if(!handler)
     {
          return;
     }

     for(const auto &listener : handler->fileDropListeners)
     {
          listener(window, count, paths);
     }
}

void InputHandler::mouseMoveCallback(GLFWwindow *window, double x, double y)
{
     InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
     if(!handler)
     {
          return;
     }

     for(const auto &listener : handler->moveListeners)
     {
          listener(window, x, y);
     }
}
