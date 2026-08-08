#pragma once
#include "../Physic_object.h"

class Tank : public Physic_object
{
    private:
    double fuel_mass;

    public:
    Tank(Vector3D pos, double mass, double fuel_m) : 
    Physic_object(pos, mass+fuel_m), fuel_mass(fuel_m) {};

    double get_fuel_mass() const {return fuel_mass;} ; 
    void reduce_fuel_mass(double amount) {
        fuel_mass -= amount;
        if(fuel_mass <=0) 
            {fuel_mass = 0;
            std::cout<< "Tank is empty" << '\n';
            };
        
            };
    

};