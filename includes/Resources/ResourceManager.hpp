#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

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

        static inline void init()
        {
            defaultTexture.load();
            defaultShader.load();
        }
        
        static Texture getTexture(std::string name, bool mipmap = true, bool hdr = false);
        static Shader getShader(std::string name_vs, std::string name_fs);

    private:
        static LRUCache<64> cache;
};

#endif