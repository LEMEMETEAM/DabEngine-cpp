#include "Resources/ResourceManager.hpp"

Texture ResourceManager::defaultTexture = Texture(4, 4, true, false);
Shader ResourceManager::defaultShader = Shader(VS_SOURCE, FS_SOURCE, true);
LRUCache<64> ResourceManager::cache = LRUCache<64>();

Texture ResourceManager::getTexture(std::string name, bool mipmap, bool hdr)
{
    Texture* res = (Texture*)cache.get(name);
    if(res == NULL)
    {
        Texture tex = Texture(name, mipmap, hdr);
        tex.load();
        if(!tex.m_ready)
        {
            return defaultTexture;
        }
        cache.add(name, tex);
        return tex;
    }
    return *res;
}

Shader ResourceManager::getShader(std::string name_vs, std::string name_fs)
{
    std::string join = name_vs+"|"+name_fs;

    Shader* res = (Shader*)cache.get(join);
    if(res == NULL)
    {
        Shader s = Shader(name_vs, name_fs, false);
        s.load();
        if(!s.m_ready)
        {
            return defaultShader;
        }

        cache.add(join, s);
        return s;
    }
    return *res;
}