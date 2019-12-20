#include "Resources/Resource.hpp"

Resource::Resource(std::string filename)
:m_filename(filename), m_ready(false)
{}

Resource::Resource()
:m_filename(""), m_ready(false)
{}

Resource::~Resource()
{
    m_ready = false;
}

void Resource::load()
{
    create();
}