#ifndef MATRIX_H_
#define MATRIX_H_

#include "Utils/Vector.hpp"

template<int C, int R, typename T>
class mat
{
    T m[C * R]{0};

    public:
        static constexpr int m_columns = C;
        static constexpr int m_rows = R;

        inline void identity()
        {
            int smallest = (C<R)?C:R;
            for(int i = 0; i < smallest; i++)
            {
                m[i*C+i] = static_cast<T>(1.0);
            }
        }

        inline mat(bool idn = false){if(idn)identity();}
        mat(const T src[C*R])
        {
            for(int i = 0; i < C*R; i++)
            {
                m[i] = src[i];
            }
        }

        inline float* get()
        {
            return m;
        }

        //adding and subtracting matrix of different size is undefined behaviour
        inline mat operator+(const mat& ref) const
        {
            mat result = *this;
            for(int i = 0; i < R * C; i++)
            {
                result.m[i] += ref.m[i];
            }
            return result;
        }

        inline mat operator-(const mat& ref) const
        {
            mat result = *this;
            for(int i = 0; i < R * C; i++)
            {
                result.m[i] -= ref.m[i];
            }
            return result;
        }

        inline mat& operator+=(const mat& ref)
        {
            for(int i = 0; i < R * C; i++)
            {
                m[i] += ref.m[i];
            }
            return this;
        }

        inline mat& operator-=(const mat& ref)
        {
            for(int i = 0; i < R * C; i++)
            {
                m[i] -= ref.m[i];
            }
            return this;
        }

        inline mat operator*(const T scalar) const
        {
            mat result = *this;
            for(int i = 0; i < R * C; i++)
            {
                result.m[i] *= scalar;
            }
            return result;
        }

        inline mat operator*(const mat& ref) const
        {
            if(R != ref.m_columns) return *this;

            mat<C, ref.m_rows, T> result;
            for(int i = 0; i < C; i++)
            {
                for(int j = 0; j < ref.m_rows; j++)
                {
                    for(int k = 0; k < R; k++)
                    {
                            result.m[i*C+j] += m[i*C+k] * ref.m[k*ref.m_columns+j];
                    }
                }
            }
            return result;
        }
};

typedef mat<4, 4, float> Matrix4f;

#endif