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

        inline int getSize(){return m_size;}
        inline int getIdx(){return m_idx;}
        inline bool hasBegun(){return m_begun;}
    private:
        VertexBuffer m_buffer;
        int m_size, m_idx = 0;
        bool m_begun = false;
};

#endif