#pragma once
#include "RawModel.h"
#include <vector>

class Loader
{
public:
    Loader();
    ~Loader();

    RawModel dataToVAO(GLfloat* data, int size);
    
private:
    GLuint createVAO();
    void storeDataInAttributeList(int attributeID, GLfloat* data, int size);
    void unbindVAO();

    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
};

