#include "GameObject.h"

GameObject::GameObject()
{
     shader = nullptr;
     model = nullptr;
     transform = new Transform();
}

GameObject::GameObject(const std::string &name)
{
     this->name = name;
     shader = nullptr;
     model = nullptr;
     transform = new Transform();
}

GameObject::~GameObject()
{
     delete shader;
     shader = nullptr;

     delete model;
     model = nullptr;

     delete transform;
     transform = nullptr;

     CG_CORE_INFO("Cleaned up GameObject");
}

void GameObject::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
     if (shader != nullptr)
     {
          shader->use();
          shader->setMatrix("view", viewMatrix);
          shader->setMatrix("projection", projectionMatrix);
          shader->setMatrix("model", transform->getModelMatrix());
          if (model != nullptr)
          {
               model->Draw(shader);
          }
     }
}

void GameObject::setupShader(const char *vertexPath, const char *fragmentPath)
{
     shader = new Shader{vertexPath, fragmentPath};
     shader->use();
     CG_CORE_INFO("Setup shader: {0}", shader->ID);
}

void GameObject::setupModel(const std::string &modelPath)
{
     model = new Model(modelPath);
     CG_CORE_INFO("Setup model");
}
