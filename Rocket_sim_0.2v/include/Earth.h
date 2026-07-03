#pragma once
#include "Physic_object.h"

class Earth : public Physic_object
{
    private:
    const double radius = 6371000.0;

    public:
    Earth () :Physic_object ({0,0,0}, 5.972E+24) {}; 

    Vector3D surfacePoint(double height_above_surface) const 
    {
        return position + Vector3D{0,radius+height_above_surface,0};
    };
};