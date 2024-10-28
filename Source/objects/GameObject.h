#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Transform.h"
#include "Model.h"
#include "Shader.h"
#include "../cgpch.h"
/// @brief A gameObject has: a transform, model, shader, collider, physics body(?), name.
class GameObject
{
private:
     std::string name;
public:
     Transform *transform = nullptr;
     Model *model = nullptr;
     Shader *shader = nullptr;
     GameObject();
     GameObject(const std::string &name);
     ~GameObject();
     void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
     void setupShader(const char *vertexPath, const char *fragmentPath);
     void setupModel(const std::string &modelPath);
};


#endif
