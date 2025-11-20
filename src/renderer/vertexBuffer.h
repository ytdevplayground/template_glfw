#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>

class VertexBuffer{

    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind();
        void Unbind();

    private:
        unsigned int m_VertexID;

};

#endif