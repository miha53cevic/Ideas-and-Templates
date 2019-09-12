#pragma once
#include "RawModel.h"
#include <vector>

class Loader
{
public:
    Loader();
    ~Loader();

    RawModel dataToVAO(GLfloat* data, int size, GLuint* indicies, int indexCount);
    
private:
    GLuint createVAO();
    void storeDataInAttributeList(int attributeID, GLfloat* data, int size);
    void unbindVAO();
    void bindIndiciesBuffer(GLuint* indicies, int size);

    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
};

