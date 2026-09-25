#pragma once
#include "../Physic_object.h"

class Tank : public Physic_object
{
    private:
    double fuel_mass_;

    public:
    Tank(Vector3D pos, double mass, double fuel_m) : 
    Physic_object(pos, mass+fuel_m), fuel_mass_(fuel_m) {};

    double get_fuel_mass() const {return fuel_mass_;} ; 
    void reduce_fuel_mass(double amount) {
        fuel_mass_ -= amount;
        if(fuel_mass_ <=0) 
            {fuel_mass_ = 0;
            std::cout<< "Tank is empty" << '\n';
            };
        
            };
    

};