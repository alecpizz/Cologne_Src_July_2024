#include "Transform.h"

Transform::Transform(glm::vec3 pos, glm::quat rot, glm::vec3 scl) : position(pos), rotation(rot), scale(scl)
{
     updateModelMatrix();
}

Transform::Transform() : position(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f)
{
     updateModelMatrix();
}

Transform::Transform(Transform &other) : position(other.position), rotation(other.rotation), scale(other.scale)
{
     updateModelMatrix();
}

Transform::~Transform()
{
}

glm::vec3 Transform::getPosition() const
{
     return position;
}

glm::quat Transform::getRotation() const
{
     return rotation;
}

glm::vec3 Transform::getScale() const
{
     return scale;
}

glm::mat4 Transform::getModelMatrix() const
{
     return model;
}

void Transform::setPosition(glm::vec3 pos)
{
     position = pos;
     updateModelMatrix();
}

void Transform::setRotation(glm::quat rot)
{
     rotation = rot;
     updateModelMatrix();
}

void Transform::setScale(glm::vec3 scl)
{
     scale = scl;
     updateModelMatrix();
}

void Transform::setTransform(glm::vec3 pos, glm::quat rot, glm::vec3 scl)
{
     position = pos;
     rotation = rot;
     scale = scl;
     updateModelMatrix();
}

void Transform::updateModelMatrix() //TODO instead of this, store an existing matrix that is just modified.
{
     glm::mat4 newModel(1.0f);
     newModel = glm::translate(newModel, position);
     newModel = newModel * glm::mat4_cast(rotation);
     newModel = glm::scale(newModel, scale);
     model = newModel;
}
