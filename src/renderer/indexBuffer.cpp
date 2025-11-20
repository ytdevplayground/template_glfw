#include "indexBuffer.h"

IndexBuffer::IndexBuffer(const void *data, unsigned int count)
: m_Count(count)
{
    glCreateBuffers(1, &m_IndexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_IndexID);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexID);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
