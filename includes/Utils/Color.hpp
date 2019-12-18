#ifndef COLOR_H_
#define COLOR_H_

#include <initializer_list>
#include <type_traits>

template<int N>
class color
{
    public:
    float c[N]{0};
    color(const int&& hex)
    {
        if(N>0)
            c[0] = ((hex >> 24) & 0xFF)/255.0f;
        if(N>1)
            c[1] = ((hex >> 16) & 0xFF)/255.0f;
        if(N>2)
            c[2] = ((hex >> 8) & 0xFF)/255.0f;
        if(N>3)
            c[3] = (hex & 0xFF)/255.0f;
    }

    color(std::initializer_list<float> l)
    {
        if(l.size() <= N)
        {
            int i = 0;
            for(float f : l)
            {
                c[i] = f;
                i++;
            }
        }
    }

    color& operator=(const int&& hex)
    {

    }
};

#endif