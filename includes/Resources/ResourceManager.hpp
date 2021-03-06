#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Cache/LRUCache.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Shader.hpp"
#include <string>
#include <initializer_list>

#define VS_SOURCE "#version 330\n\n"\
                        "layout (location = 0) in vec3 position;\n"\
                        "layout (location = 1) in vec4 color;\n"\
                        "layout (location = 2) in vec2 uvs;\n"\
                        "layout (location = 3) in vec3 normals;\n\n"\
                        "out vec3 outPosition;\n"\
                        "out vec4 outColor;\n"\
                        "out vec2 outUV;\n"\
                        "out vec3 outNormals;\n\n"\
                        "uniform mat4 m_proj;\n\n"\
                        "void main(){\n"\
                        "     gl_Position = m_proj * vec4(position, 1.0);\n"\
                        "     outPosition = position;\n"\
                        "     outColor = color;\n"\
                        "     outUV = uvs;\n"\
                        "     outNormals = normals;\n"\
                        "}\n"

#define FS_SOURCE "#version 330\n\n"\
                            "in vec4 outColor;\n"\
                            "in vec2 outUV;\n"\
                            "out vec4 finalColor;\n\n"\
                            "uniform sampler2D texture0;\n\n"\
                            "void main(){\n"\
                            "     vec4 s = texture(texture0, outUV);\n"\
                            "     finalColor = s * outColor;\n"\
                            "}\n"

class Resource;

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
        
        template<typename T, typename... Args, typename std::enable_if<std::is_base_of<Resource, T>::value>::type* = nullptr>
        static T* get(std::string name, Args&&... a);

    private:
        static LRUCache<64> cache;
};

#endif