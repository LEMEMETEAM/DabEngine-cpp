#include "Resources/Resource.hpp"

Resource::Resource(std::string filename)
:m_filename(filename), m_ready(false)
{}

Resource::Resource()
:m_filename(""), m_ready(false)
{}

Resource::~Resource()
{
    free();
    m_ready = false;
}

void Resource::free()
{
    destroy();
}

void Resource::load()
{
    create();
}