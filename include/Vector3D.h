#pragma once
#include <math.h>
#include <assert.h>

class Vector3D {
    public:
    double x,y,z;

    Vector3D(double x=0, double y=0, double z=0) : x(x), y(y),z(z) {
        //if (x<0 || y < 0 || z < 0)  error hundle
    };

    Vector3D operator+(const Vector3D& other) const{
        return Vector3D(x+other.x, y+other.y, z+other.z);
    }
    Vector3D operator-(const Vector3D& other) const{
        return Vector3D(x-other.x, y-other.y, z-other.z);
    }
    Vector3D operator*(double scalar) const {
        return Vector3D(x*scalar, y*scalar , z*scalar);
    }
    Vector3D operator/(double division) const {
        assert(division!=0);
        return Vector3D(x/division ,y/division ,z/division);
    }

    double magnitude() const {
        return std::sqrt(x*x+y*y+z*z);
    }
    
    Vector3D normalize() const {
        double mag = magnitude();
        if (mag < 1e-10) return Vector3D(0.0,0.0,0.0); //для float/double сравнение на точное равенство нулю — рискованная штука из-за погрешностей вычислений
        //                                              лучше сравнивать с маленьким эпсилоном, например if (mag < 1e-10).
        return Vector3D(x/mag, y/mag, z/mag);
    }
};