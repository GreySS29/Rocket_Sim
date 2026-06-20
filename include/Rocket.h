#pragma once
#include "RocketState.h"
#include "Vector3D.h"

class Rocket {
private:
    RocketState state;
    double thrust; //H
    double fuel_consumption; // kg/s
    double rocket_mass; // kg
    double tx,ty,tz;
public:
    Rocket(double mass , double fuel)
    : state(mass,fuel),thrust(1500000.0) , fuel_consumption(500.0) {
        rocket_mass = state.mass - state.fuel;
        //exception
        tx=0.0 ; ty= 1.0 ; tz=0.0; // up
    }

    const RocketState& getState() const  {return  state;};
    RocketState& getState()   {return  state;};
    double getFuel_consuption() const {return fuel_consumption;};
    double getRocket_mass() const {return rocket_mass; }
    Vector3D getThrustForce() const {
        if (state.fuel == 0) return Vector3D(0,0,0);
        return Vector3D(tx,ty,tz)*thrust;
    }
};