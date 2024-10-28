#include "PhysicsDebugRenderer.h"

void MyDebugRenderer::DrawLine(RVec3Arg inFrom, RVec3Arg inTo, ColorArg inColor)
{
    if(line != nullptr)
    {
        glm::vec3 start = glm::vec3(inFrom.GetX(), inFrom.GetY(), inFrom.GetZ());
        glm::vec3 end = glm::vec3(inTo.GetX(), inTo.GetY(), inTo.GetZ());
        glm::vec3 color = glm::vec3(inColor.r, inColor.g, inColor.b);
        line->draw(start, end, color, project, view);
    }
}

void MyDebugRenderer::DrawTriangle(RVec3Arg inV1, RVec3Arg inV2, RVec3Arg inV3, ColorArg inColor,
                                   DebugRenderer::ECastShadow inCastShadow)
{

}

void MyDebugRenderer::DrawText3D(RVec3Arg inPosition, const string_view &inString, ColorArg inColor, float inHeight)
{

}

MyDebugRenderer::MyDebugRenderer()
{
    this->line = new Line(RESOURCES_PATH "assets/shader.vs", RESOURCES_PATH "assets/lightShader.fs");
}

MyDebugRenderer::~MyDebugRenderer()
{
    delete line;
    line = nullptr;
}

void MyDebugRenderer::update(glm::mat4 view, glm::mat4 project)
{
    this->view = view;
    this->project = project;
}
