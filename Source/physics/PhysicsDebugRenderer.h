#ifndef PHYSICSDEBUGRENDERER_H
#define PHYSICSDEBUGRENDERER_H

#include "../cgpch.h"
#include "../camera/MainCamera.h"
#include "../objects/Line.h"


using namespace JPH;

class MyDebugRenderer : public DebugRendererSimple
{
public:
    MyDebugRenderer();
    void update(glm::mat4 view, glm::mat4 project);
    ~MyDebugRenderer();
    virtual void DrawLine(RVec3Arg inFrom, RVec3Arg inTo, ColorArg inColor) override;

    virtual void
    DrawTriangle(RVec3Arg inV1, RVec3Arg inV2, RVec3Arg inV3, ColorArg inColor, ECastShadow inCastShadow) override;

    virtual void
    DrawText3D(RVec3Arg inPosition, const string_view &inString, ColorArg inColor, float inHeight) override;

private:
    glm::mat4 view, project;
    Line *line;
};

#endif PHYSICSDEBUGRENDERER_H
