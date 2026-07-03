#pragma once
#include "Vector3D.h"

class Physic_object 
{
private:


protected:
    Vector3D position;
    double mass;
    Physic_object(Vector3D pos, double m) : position(pos), mass(m) {};
    virtual ~Physic_object() = default;

public:

    double get_mass() const { return mass; }
    Vector3D get_position() const { return position; }
    
    
};


