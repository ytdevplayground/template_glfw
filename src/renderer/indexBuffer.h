#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <glad/glad.h>

class IndexBuffer {

    public:
        IndexBuffer(const void* data, unsigned int count);
        ~IndexBuffer();

        void Bind();
        void Unbind();

        inline unsigned int GetCount() const {return m_Count;}

    private:
        unsigned int m_IndexID;
        unsigned int m_Count;
};

#endif