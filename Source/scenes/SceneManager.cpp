#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
     for(int i = 0; i < gameObjects.size(); i++)
     {
          delete gameObjects[i];
          gameObjects[i] = nullptr;
     }
    CG_CORE_INFO("Cleaned up scene GameObjects");
}

void SceneManager::updateObjects(glm::mat4 view, glm::mat4 projection)
{
     for(auto & gameObject : gameObjects)
     {
          if(gameObject != nullptr)
          {
               gameObject->update(view, projection);
          }
     }
}

GameObject *SceneManager::getNewGameObject()
{
     GameObject *newObj = new GameObject();
     gameObjects.push_back(newObj);
     return newObj;
}
