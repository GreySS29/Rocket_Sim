#pragma once
#include "Physic_object.h"

class Tank : public Physic_object
{
    private:
    double fuel_mass;

    public:
    Tank(Vector3D pos, double mass, double fuel_m) : Physic_object(pos, mass+fuel_m), fuel_mass(fuel_m) {};

};