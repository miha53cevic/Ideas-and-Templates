#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::prepeare()
{
}

void Renderer::render(const RawModel& model)
{
    glBindVertexArray(model.get_vaoID());
    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
    glBindVertexArray(0);
}

