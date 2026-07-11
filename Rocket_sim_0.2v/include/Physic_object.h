#pragma once
#include "Vector3D.h"
#include "System_numbers.h"
#include "Constants.h"



class Physic_object 
{
private:


protected:
    Vector3D position;
    double mass; //kg 
    Physic_object(Vector3D pos, double m) : position(pos), mass(m) {};
    virtual ~Physic_object() = default;

public:

    double get_mass() const { return mass; }
    Vector3D get_position() const { return position ; } 
    Vector3D get_position_above_surface() const { return (position-Vector3D {0,RADIUS_E,0}); }
    
    void reduce_mass(double amount) {mass-=amount;}
};


