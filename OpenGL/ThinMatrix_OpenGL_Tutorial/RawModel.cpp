#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, int verticiesCount)
{
    m_vaoID = vaoID;
    m_verticiesCount = verticiesCount;
}

GLuint RawModel::get_vaoID() const
{
    return m_vaoID;
}

int RawModel::getVertexCount() const
{
    return m_verticiesCount;
}
