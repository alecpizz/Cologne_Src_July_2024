//
// Created by alecp on 5/30/2024.
//

#include "Line.h"
#include "../cgpch.h"

Line::Line(const char *vertexPath, const char *fragmentPath)
{
    vertices[0] = 1.0f;
    vertices[1] = 1.0f;
    vertices[2] = 1.0f;
    vertices[3] = 0.0f;
    vertices[4] = 0.0f;
    vertices[5] = 0.0f;
    indicies[0] = 0;
    indicies[1] = 1;
    shader = new Shader(vertexPath, fragmentPath);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Line::~Line()
{
    delete shader;
    shader = nullptr;
}

void Line::draw(glm::vec3 start, glm::vec3 end, glm::vec3 color, glm::mat4 projection, glm::mat4 view)
{
    glDisable(GL_DEPTH_TEST);
    vertices[0] = start.x;
    vertices[1] = start.y;
    vertices[2] = start.z;
    vertices[3] = end.x;
    vertices[4] = end.y;
    vertices[5] = end.z;
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    shader->use();
    shader->setVec3("color", color);
    shader->setMatrix("projection", projection);
    shader->setMatrix("view", view);
    glm::mat4 model = glm::mat4(1.0);
    shader->setMatrix("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}
