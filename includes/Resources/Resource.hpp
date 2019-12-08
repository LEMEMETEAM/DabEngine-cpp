#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>

class Resource
{
    public:
        Resource();
        Resource(std::string filename);
        ~Resource();

        void load();

        bool m_ready;
    
    protected:
        virtual void create() = 0;
        virtual void destroy() = 0;
        void free();
        std::string m_filename;
};

#endif