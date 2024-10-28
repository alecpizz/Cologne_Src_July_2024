#ifndef ENGINE_H
#define ENGINE_H
#include "cgpch.h"
#include "input/InputHandler.h"
#include "debug/DebugUI.h"
#include "camera/MainCamera.h"
#include "scenes/SceneManager.h"
#include "objects/Skybox.h"
#include "physics/PhysicsManager.h"
#include "physics/PhysicsDebugRenderer.h"
#include "renderer/Renderer.h"
class Engine
{
public:
     Engine();
     ~Engine();
     int init();
     void run();
     GLFWwindow *window;
     InputHandler *inputHandler;
     DebugUI *debugUI;
     MainCamera *camera;
     SceneManager *sceneManager;
     SkyBox *sky; //TODO put in renderer
     PhysicsManager *physicsManager;
     Renderer *renderer;
};

#endif
