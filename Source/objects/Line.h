//
// Created by alecp on 5/30/2024.
//

#ifndef HELLOWORLD_LINE_H
#define HELLOWORLD_LINE_H
#include "Shader.h"
#include "../cgpch.h"
class Line
{
private:
    Shader *shader;
    unsigned int VBO, VAO, EBO;
    float vertices[6];
    unsigned int indicies[2];
public:
    Line(const char *vertexPath, const char *fragmentPath);
    ~Line();
    void draw(glm::vec3 start, glm::vec3 end, glm::vec3 color, glm::mat4 projection, glm::mat4 view);
};


#endif //HELLOWORLD_LINE_H
