#include "Cache/LRUCache.hpp"
#include "Resources/Resource.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Shader.hpp"
#include <string>

#define VS_SOURCE "#version 330\n\n"\
                        "layout (location = 0) in vec3 position;\n"\
                        "layout (location = 1) in vec4 color;\n"\
                        "layout (location = 2) in vec2 uvs;\n"\
                        "layout (location = 3) in vec3 normals;\n\n"\
                        "out vec3 outPosition;\n"\
                        "out vec4 outColor;\n"\
                        "out vec2 outUV;\n"\
                        "out vec3 outNormals;\n\n"\
                        "void main(){\n"\
                        "     gl_Position = vec4(position, 1.0);\n"\
                        "     outPosition = position;\n"\
                        "     outColor = color;\n"\
                        "     outUV = uvs;\n"\
                        "     outNormals = normals;\n"\
                        "}\n"

#define FS_SOURCE "#version 330\n\n"\
                            "in vec4 outColor;\n"\
                            "out vec4 finalColor;\n\n"\
                            "void main(){\n"\
                            "     finalColor = outColor;\n"\
                            "}\n"
class ResourceManager
{
    public:
        static Texture defaultTexture;
        static Shader defaultShader;

        static inline Texture getTexture(std::string name, bool mipmap = true, bool hdr = false)
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
        
        static inline Shader getShader(std::string name_vs, std::string name_fs)
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

    private:
        static LRUCache<64> cache;
};

Texture ResourceManager::defaultTexture = Texture(4, 4, true, false);
Shader ResourceManager::defaultShader = Shader(VS_SOURCE, FS_SOURCE, true);