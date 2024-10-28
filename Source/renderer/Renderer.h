#ifndef RENDERER_H
#define RENDERER_H

#include "../objects/Shader.h"
#include "../objects/GameObject.h"

class Renderer
{
public:
    Renderer();

    ~Renderer();

    void update(glm::mat4 projection, glm::mat4 view);
    void draw(GameObject *gameObject);
    void postUpdate(glm::mat4 projection, glm::mat4 view, glm::vec3 viewPos);

private:
    unsigned int gBuffer;
    unsigned int gPosition;
    unsigned int gNormal;
    unsigned int gAlbedoSpec;
    unsigned int rboDepth;
    unsigned int screenQuadVAO = 0;
    unsigned int screenQuadVBO;
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    Shader *gShader;
    Shader *litShader;
    Shader *unlitShader;
    void drawQuad();
    void drawCube();
};

#endif
