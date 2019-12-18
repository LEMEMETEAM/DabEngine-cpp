#include "Utils/Matrix.hpp"
#include "Vector.hpp"

#define PI 3.1415926535897932384626433

namespace dmath
{

    inline float toRadians(float deg)
    {
        return deg * PI/180.0f;
    }

    inline Matrix4f buildMatrixOrtho(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f)
    {
        float m[16] =   {
                        2.0f/(right-left)   , 0                 , 0                 , -((right+left)/(right-left)),
                        0                   , 2.0f/(top-bottom) , 0                 , -((top+bottom)/(top-bottom)),
                        0                   , 0                 , -2.0f/(far-near)  , -((far+near)/(far-near)),
                        0                   , 0                 , 0                 , 1
                        };
        return Matrix4f(m);
    }

    inline Matrix4f buildMatrixPerspective(float fov, float aspect, float zn, float zf)
    {
        const float f = 1.0f / std::tan(toRadians(fov)/2.0f);

        const float q = (zf+zn)/(zn-zf);
        const float qn = (2*zf*zn)/(zn-zf);

        float m[16] =   {
                        f/aspect, 0, 0, 0,
                        0       , f, 0, 0,
                        0       , 0, q,qn,
                        0       , 0,-1, 0
                        };
        return Matrix4f(m);
    }

    inline Matrix4f buildMatrixLookAt(Vector3f eye, Vector3f target, Vector3f up)
    {
        Vector3f zAxis = (eye-target).normalize();
        Vector3f xAxis = up.cross(zAxis).normalize();
        Vector3f yAxis = zAxis.cross(xAxis);

        float m[16] =   {
                        xAxis.x(), xAxis.y(), xAxis.z(), -xAxis.dot(eye),
                        yAxis.x(), yAxis.y(), yAxis.z(), -yAxis.dot(eye),
                        zAxis.x(), zAxis.y(), zAxis.z(), -zAxis.dot(eye),
                        0        , 0        , 0        , 1              
                        };
        return Matrix4f(m);
    }
}