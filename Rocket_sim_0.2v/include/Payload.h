#pragma once
#include "Physic_object.h"

class Payload : public Physic_object {
    private:
    Vector3D velocity;


    public:
    Payload(Vector3D pos, double mas, double c_d, double area,  Vector3D vel): Physic_object {pos,mas,c_d,area} 
    {
        velocity = Vector3D(vel);
    };

    
    Vector3D get_velocity() const {return velocity;};
    
};