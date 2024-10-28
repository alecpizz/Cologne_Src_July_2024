#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../cgpch.h"
class Transform
{
public:
     Transform(glm::vec3 pos, glm::quat rot, glm::vec3 scl);
     Transform();
     Transform(Transform &other);
     ~Transform();

     glm::vec3 getPosition() const;
     glm::quat getRotation() const;
     glm::vec3 getScale() const;
     glm::mat4 getModelMatrix() const;

     void setPosition(glm::vec3 pos);
     void setRotation(glm::quat rot);
     void setScale(glm::vec3 scl);
     void setTransform(glm::vec3 pos, glm::quat rot, glm::vec3 scl);

private:
     glm::vec3 position;
     glm::quat rotation;
     glm::vec3 scale;
     glm::mat4 model;

     void updateModelMatrix();
};
#endif
