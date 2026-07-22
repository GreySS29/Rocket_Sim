#pragma once 
#include "Physic_object.h"

class Engine : public Physic_object {
private:
    double thrust_; //H
    double fuel_consumption_;// kg/s
    Vector3D thrust_direction_; 
    // bool fuel_ = true; // fluel from tank 
    // bool status_ = false; // enable or disable 

public:
    Engine(Vector3D position, double mass,double thrust, double fuel_consumption)
        : Physic_object{position, mass},
          thrust_(thrust),
          fuel_consumption_(fuel_consumption),
          thrust_direction_{0.0, 1.0, 0.0}
    {
    }

    double get_thrust() const { return thrust_; }
    // void run_engine(bool command) {
    //     if (command == true) {
    //         status_ = true;
    //         std::cout<<"Engine was run"<<'\n';
    //     } else {
    //         status_ == false;
    //         thrust_ = 0;
    //         std::cout<<"Engine was turn off"<<'\n';
    //     }
        
    // }
    Vector3D get_thrust_vec(){
        return thrust_direction_ * thrust_;
    }
    double get_fuel_consumption() const { return fuel_consumption_; }

    // void set_fuel(bool fuel) { fuel_ = fuel; }

    // Vector3D get_thrust_force() const {
    //     if (fuel_ == false) return Vector3D{0, 0, 0};
    //     
    // }

    Vector3D set_thrust_direction(double x, double y, double z) {
        thrust_direction_ = Vector3D{x, y, z};
        return thrust_direction_;
    }

    Vector3D get_thrust_direction() const {
        return thrust_direction_;
    }
};