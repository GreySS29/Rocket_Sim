#pragma once
#include "RocketState.h"
#include "Vector3D.h"

class Rocket {
private:
    RocketState state;
    double _thrust; //H
    double _fuel_consumption; // kg/s
    double _rocket_mass; // kg
    Vector3D _thrust_dir;
public:
    Rocket(double mass , double fuel , double thrust, double fuel_consumption)
    : state(mass,fuel),_thrust(thrust) , _fuel_consumption(fuel_consumption) {
        _rocket_mass = state.mass - state.fuel;
        //exception
        _thrust_dir = Vector3D(0.0,1.0,0.0); // up
    }

    const RocketState& getState() const  {return  state;};
    RocketState& getState()   {return  state;};
    double getFuel_consuption() const {return _fuel_consumption;};
    double getRocket_mass() const {return _rocket_mass; }
    Vector3D getThrustForce() const {
        if (state.fuel == 0) return Vector3D(0,0,0);
        return _thrust_dir*_thrust;
    }
    Vector3D setThrustDirection (double x, double y, double z) 
    {
        return _thrust_dir = Vector3D(x,y,z);
    }
    const Vector3D getThustDirection () const
    {
        return _thrust_dir;
    }
};