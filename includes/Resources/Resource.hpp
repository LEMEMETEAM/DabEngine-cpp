#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>

class Resource
{
    public:
        Resource();
        Resource(std::string filename);
        virtual ~Resource();

        void load();

        bool m_ready;
    
    protected:
        virtual void create() = 0;
        std::string m_filename;
};

#endif