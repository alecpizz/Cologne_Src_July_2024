#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "../cgpch.h"
class InputHandler
{
public:
     InputHandler(GLFWwindow *window);
     ~InputHandler();
     void addKeyListener(const std::function<void(GLFWwindow *, int, int, int, int)> &listener);
     void addMouseButtonListener(const std::function<void(GLFWwindow *, int, int, int)> &listener);
     void addMouseScrollListener(const std::function<void(GLFWwindow *, int, int)> &listener);
     void addFileDropListener(const std::function<void(GLFWwindow *, int, const char **)> &listener);
     void addMouseMoveListener(const std::function<void(GLFWwindow *, double, double)> &listener);

private:
     GLFWwindow *window;
     std::vector<std::function<void(GLFWwindow *, int, int, int, int)>> keyListeners;
     std::vector<std::function<void(GLFWwindow *, int, int, int)>> mouseButtonListeners;
     std::vector<std::function<void(GLFWwindow *, int, int)>> scrollListeners;
     std::vector<std::function<void(GLFWwindow *, int, const char **)>> fileDropListeners;
     std::vector<std::function<void(GLFWwindow *, double, double)>> moveListeners;

     static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
     static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
     static void mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
     static void fileDropCallback(GLFWwindow *window, int count, const char **paths);
     static void mouseMoveCallback(GLFWwindow *window, double x, double y);
};

#endif
