#include "Resources/ResourceManager.hpp"
#include <type_traits>

Texture ResourceManager::defaultTexture = Texture(4, 4, true, false);
Shader ResourceManager::defaultShader = Shader(VS_SOURCE, FS_SOURCE, true);
LRUCache<64> ResourceManager::cache = LRUCache<64>();

template<typename T, typename... Args, typename std::enable_if<std::is_base_of<Resource, T>::value>::type* = nullptr>
T* ResourceManager::get(std::string name, Args&&... args)
{
    Resource* res = static_cast<Resource*>(cache.get(name));
    if(!res)
    {
        T new_res = T(args...);
        new_res.load();
        if(!new_res.ready)
        {
            if(std::is_same<T, Texture>::value)
            {
                return defaultTexture;
            }
            else if(std::is_same<T, Shader>::value)
            {
                return defaultShader;
            }
        }
        else
        {
            cache.add(name, new_res);
            return static_cast<Resource*>(cache.get(name));
        }
        
    }
    else
    {
        return static_cast<T*>(res);
    }
}