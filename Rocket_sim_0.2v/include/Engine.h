#pragma once 
#include "Physic_object.h"

class Engine : public Physic_object {
private:
    double _thrust; //H
    double _fuel_consumption;// kg/s
    Vector3D _thrust_direction; 
    bool _fuel = true;

public:
    Engine(Vector3D position, double mass,double thrust, double fuel_consumption)
        : Physic_object{position, mass},
          _thrust(thrust),
          _fuel_consumption(fuel_consumption),
          _thrust_direction{0.0, 1.0, 0.0}
    {
    }

    double get_thrust() const { return _thrust; }
    double get_fuel_consumption() const { return _fuel_consumption; }

    void set_fuel(bool fuel) { _fuel = fuel; }

    Vector3D get_thrust_force() const {
        if (!_fuel) return Vector3D{0, 0, 0};
        return _thrust_direction * _thrust;
    }

    Vector3D set_thrust_direction(double x, double y, double z) {
        _thrust_direction = Vector3D{x, y, z};
        return _thrust_direction;
    }

    Vector3D get_thrust_direction() const {
        return _thrust_direction;
    }
};