#pragma once
#include "../Physic_object.h"

class Payload : public Physic_object {
    private:
    Vector3D velocity;
    quantity<m2> a_wet;


    public:
    Payload(Vector3D pos, double mas, double c_d, double area , quantity<m2> area_wet): Physic_object {pos,mas,c_d,area} , a_wet(area_wet)
    {
        velocity = Vector3D{0,0,0};
    };

    
    Vector3D get_velocity() const {return velocity;};
    quantity<m2> get_a_wet() const {return a_wet;};
    
};