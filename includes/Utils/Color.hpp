#ifndef COLOR_H_
#define COLOR_H_

template<int N>
class color
{
    public:
    int c[N]{0};
    color(const int&& hex)
    {
        if(N>0)
            c[0] = (hex >> 24) & 0xFF;
        if(N>1)
            c[1] = (hex >> 16) & 0xFF;
        if(N>2)
            c[2] = (hex >> 8) & 0xFF;
        if(N>3)
            c[3] = hex & 0xFF;
    }

    color& operator=(const int&& hex)
    {
        
    }
};

#endif