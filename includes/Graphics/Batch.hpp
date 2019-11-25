#ifndef BATCH_H_
#define BATCH_H_

#include <vector>
#include "Graphics/VertexBuffer.hpp"

class Batch
{
    public:
        Batch(int size);
        ~Batch();

        void begin();
        void add(float* data, int length);
        void end();
        void flush();

        int getSize(){return m_size;}
        int getIdx(){return m_idx;}
        bool hasBegun(){return m_begun;}
    private:
        VertexBuffer m_buffer;
        int m_size, m_idx;
        bool m_begun;
};

#endif