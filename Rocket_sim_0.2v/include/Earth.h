#pragma once
#include "Physic_object.h"

class Earth : public Physic_object
{
    private:
    const double RADIUS_E = 6371000.0; //m
    const double ATMOSPHERE_HEIGHT = 100000.0;//m 
    const double AIR_DENSITY_SURFACE = 1.225; // kg/m3

    public:
    Earth () :Physic_object ({0,0,0}, 5.972E+24) {}; 

    Vector3D surfacePoint(double height_above_surface) const 
    {
        return position + Vector3D{0,RADIUS_E+height_above_surface,0};
    };

    double get_air_density(double height) const 
    {
        if (height >= ATMOSPHERE_HEIGHT) return 0; // approxim .. ?
        return AIR_DENSITY_SURFACE * std::exp(-height/8500); //exp==pow
    }

    Vector3D get_dragForce_vec(const auto& object)
    {
        double density = getAirDensity(object.get_position().y);
        if (density ==0) return Vector3D(0,0,0);
    }
};