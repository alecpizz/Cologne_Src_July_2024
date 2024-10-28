#ifndef SHADER_H
#define SHADER_H

#include "../cgpch.h"

class Shader
{
public:
     unsigned int ID;
     Shader(const char *vertexPath, const char *fragmentPath);
     Shader(const char *computePath);
     ~Shader();
     void use();
     void setBool(const std::string &name, bool value) const;
     void setInt(const std::string &name, int value) const;
     void setFloat(const std::string &name, float value) const;
     void setMatrix(const std::string &name, glm::mat4 value) const;
     void setVec3(const std::string &name, glm::vec3 value) const;
     void setVec3(const std::string &name, float x, float y, float z) const;
     void setuVec3(const std::string &name, glm::uvec3 value) const;
     void setuVec2(const std::string &name, glm::uvec2 value) const;
private:
};

#endif
