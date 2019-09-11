#pragma once
#include <GL/glew.h>

class RawModel
{
public:
    RawModel(GLuint vaoID, int verticiesCount);

    GLuint get_vaoID() const;
    int getVertexCount() const;
    
private:
    GLuint m_vaoID;
    int m_verticiesCount;
};

