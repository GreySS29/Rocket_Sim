#pragma once 
#include "../Physic_object.h"
#include <math.h>
#include <numbers>

class Engine : public Physic_object {
private:
    double thrust_; //H
    double fuel_consumption_;// kg/s
    Vector3D thrust_direction_; 

public:
    Engine(Vector3D position, double mass,double thrust, double fuel_consumption)
        : Physic_object{position, mass},
          thrust_(thrust),
          fuel_consumption_(fuel_consumption),
          thrust_direction_{0.0, 1.0, 0.0}
          {}

    double get_thrust() const { return thrust_; }
    double get_fuel_consumption() const { return fuel_consumption_; }
    Vector3D get_thrust_vec(){ return thrust_direction_ * thrust_;}
    Vector3D get_thrust_direction() const {return thrust_direction_;}
    
    
    Vector3D set_thrust_direction(double angle_deg) {
    double angle_rad = angle_deg * std::numbers::pi / 180.0;  // degrees to radian 
    thrust_direction_ = Vector3D{std::cos(angle_rad), std::sin(angle_rad), 0.0};
    return thrust_direction_;
}

    
};