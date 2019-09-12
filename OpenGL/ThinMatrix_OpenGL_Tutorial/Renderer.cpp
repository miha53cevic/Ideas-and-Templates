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
    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

