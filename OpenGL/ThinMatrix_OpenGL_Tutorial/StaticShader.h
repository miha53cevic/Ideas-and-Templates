#pragma once
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
    StaticShader()
        : ShaderProgram("Shaders/vertexShader.txt", "Shaders/fragmentShader.txt")
    {}

private:
    void bindAttributes() override
    {
        bindAttribute(0, "position");
    }

private:
};
