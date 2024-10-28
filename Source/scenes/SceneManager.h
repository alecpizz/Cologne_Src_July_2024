#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "../cgpch.h"
#include "../objects/GameObject.h"

class SceneManager
{
private:
public:
     std::vector<GameObject*> gameObjects;
     SceneManager();
     ~SceneManager();
     void updateObjects(glm::mat4 view, glm::mat4 projection);
     GameObject *getNewGameObject();
};


#endif
