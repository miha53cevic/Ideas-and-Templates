#include "Loader.h"

Loader::Loader()
{
}

Loader::~Loader()
{
    // Cleanup
    for (auto& i : m_vaos)
    {
        glDeleteVertexArrays(1, &i);
    }

    for (auto& i : m_vbos)
    {
        glDeleteBuffers(1, &i);
    }
}

RawModel Loader::dataToVAO(GLfloat * data, int size)
{
    GLuint VAO = createVAO();
    storeDataInAttributeList(0, data, size);
    unbindVAO();

    return RawModel(VAO, size / 3);
}

GLuint Loader::createVAO()
{
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Store VAO for cleanup later
    m_vaos.push_back(VAO);

    return VAO;
}

void Loader::storeDataInAttributeList(int attributeID, GLfloat* data, int size)
{
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // Store VBO for cleanup later
    m_vbos.push_back(VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // sizeof kada se salje array preko funkcije gleda velicinu pointera a ne velicinu array-a
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, data, GL_STATIC_DRAW);

    glVertexAttribPointer(attributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attributeID);

    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}
