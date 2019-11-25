#ifndef RESOURCE_H_
#define RESOURCE_H_

class Resource
{
    public:
        Resource();
        Resource(const char* filename);
        ~Resource();

        void load();
    
    protected:
        virtual void create() = 0;
        virtual void destroy() = 0;
        void free();
        bool m_ready;
        const char* m_filename;
};

#endif