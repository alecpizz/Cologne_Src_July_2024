#ifndef DEBUG_UI
#define DEBUG_UI
#include "../cgpch.h"
class DebugUI
{
public:
     DebugUI(GLFWwindow *window);
     ~DebugUI();
     void preRender();
     void render();
     void postRender();
     bool isKeyboardAvaliable();
     bool isMouseAvaliable();
private:
     void buildUI();
     bool ui_active = false;
     float sample_color[4];
};

#endif
