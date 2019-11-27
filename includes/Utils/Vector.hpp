#ifndef VECTOR_H_
#define VECTOR_H_

#include <type_traits>
#include <math.h>
#include <limits>

template<int L, typename T>
class vec
{

    T v[L]{0};

public:

    vec(){}
    template<int X = L, typename std::enable_if<(X >= 2)>::type* = nullptr>
    vec(T _x, T _y){v[0] = _x; v[1] = _y;}
    template<int X = L, typename std::enable_if<(X >= 3)>::type* = nullptr>
    vec(T _x, T _y, T _z){v[0] = _x; v[1] = _y; v[2] = _z;}
    template<int X = L, typename std::enable_if<(X >= 4)>::type* = nullptr>
    vec(T _x, T _y, T _z, T _w){v[0] = _x; v[1] = _y; v[2] = _z; v[3] = _w;}

    template<int X = L, typename std::enable_if<(X >= 1)>::type* = nullptr>
    inline T& x(){return v[0];}
    template<int X = L, typename std::enable_if<(X >= 2)>::type* = nullptr>
    inline T& y(){return v[1];}
    template<int X = L, typename std::enable_if<(X >= 3)>::type* = nullptr>
    inline T& z(){return v[2];}
    template<int X = L, typename std::enable_if<(X >= 4)>::type* = nullptr>
    inline T& w(){return v[3];}

    // template<int X = N, int N2, std::enable_if<(x != N2)>::type* = nullptr>
    

    inline vec operator-() const
    {
        vec result = *this;
        for(T& c : result.v)
        {
            c = -c;
        }
        return result;
    }

    inline vec operator+(const vec& ref) const
    {
        vec result = *this;
        for(int i = 0; i < L; i++)
        {
            result.v[i] += ref.v[i];
        }
        return result;
    }

    inline vec operator-(const vec& ref) const
    {
        vec result = *this;
        for(int i = 0; i < L; i++)
        {
            result.v[i] -= ref.v[i];
        }
        return result;
    }

    inline vec& operator+=(const vec& ref) 
    {
        for(int i = 0; i < L; i++)
        {
            v[i] += ref.v[i];
        }
        return this;
    }

    inline vec& operator-=(const vec& ref)
    {
        for(int i = 0; i < L; i++)
        {
            v[i] -= ref.v[i];
        }
        return this;
    }

    inline vec operator*(const T scalar) const
    {
        vec result = *this;
        for(T& c : result.v)
        {
            c *= scalar;
        }
        return result;
    }

    inline vec operator*(const vec& ref) const
    {
        vec result = *this;
        for(int i = 0; i < L; i++)
        {
            result.v[i] *= ref.v[i];
        }
        return result;
    }

    inline vec& operator*=(const T scalar)
    {
        for(T& c : v)
        {
            c *= scalar;
        }
        return this;
    }

    inline vec& operator*=(const vec& ref)
    {
        for(int i = 0; i < L; i++)
        {
            v[i] *= ref.v[i];
        }
        return this;
    }

    inline vec operator/(const T scalar)
    {
        vec result = *this;
        for(T& c : result.v)
        {
            c /= scalar;
        }
        return result;
    }

    inline vec& operator/=(const T scalar)
    {
        for(T& c : v)
        {
            c /= scalar;
        }
        return this;
    }

    inline T operator[](int index) const{return v[index];}
    inline T& operator[](int index){return v[index];}

    inline T length() const
    {
        T l = 0;
        for(const T& c : v)
        {
            l += c * c;
        }
        return std::sqrt(l);
    }

    inline T distance(const vec& ref)
    {
        T d = 0;
        for(int i = 0; i < L; i++)
        {
            d += (ref.v[i]-v[i])*(ref.v[i]-v[i]);
        }
        return std::sqrt(d);
    }

    template<int X = L, typename std::enable_if<(X == 3)>::type* = nullptr>
    inline vec cross(const vec& ref)
    {
        return vec((v[1] * ref.v[2]) - (v[2] * ref.v[1]),
                    (v[2] * ref.v[0]) - (v[0] * ref.v[2]),
                    (v[0] * ref.v[1]) - (v[1] * ref.v[0]));
    }

    inline T dot(const vec& ref)
    {
        T d = 0;
        for(int i = 0; i < L; i++)
        {
            d += ref.v[i]*v[i];
        }
        return d;
    }

    inline vec& normalize()
    {
        T n = 0;
        for(T& c : v)
        {
            n += c * c;
        }

        if(n == 1) return this;

        n = std::sqrt(n);
        if(n <= std::numeric_limits<T>::min()) return this;

        for(T& c : v)
        {
            c /= n;
        }

        return this;
    }
};

typedef vec<2, float> Vector2f;
typedef vec<3, float> Vector3f;
typedef vec<4, float> Vector4f;

#endif