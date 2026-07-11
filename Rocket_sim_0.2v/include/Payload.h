#pragma once
#include "Physic_object.h"

class Payload : public Physic_object {
    private:
    const double C_D = 0.3; //Коэффициент сопротивления
    const double AREA = 10.0;
    Vector3D velocity;


    public:
    Payload(Vector3D pos, double mas, Vector3D vel): Physic_object {pos,mas} 
    {
        velocity = Vector3D(vel);
    };
    Vector3D get_velocity() const {return velocity;};
    double get_C_D() const {return C_D;};
    double get_AREA() const {return AREA;};
};