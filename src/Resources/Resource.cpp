#include "Resources/Resource.hpp"

Resource::Resource(const std::string& filename)
:m_filename(filename)
{}

Resource::Resource()
:m_filename("")
{}

Resource::~Resource()
{
    m_ready = false;
}

void Resource::load()
{
    create();
}