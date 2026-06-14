#include "../RocketState.cpp"
#include "../Vector3D.cpp"

class Rocket {
private:
    RocketState state;
    double thrust; //H
    double fuel_consumption; // kg/s
    double rocket_mass; // kg
    double tx,ty,tz;
public:
    Rocket(double thrust = 1500000, double fuel_cons= 500)
    : thrust(thrust) , fuel_consumption(fuel_cons) {
        rocket_mass = state.mass - state.fuel;
        //exception
        tx=0 ; ty= 1 ; tz=0; // up
    }

    RocketState getState() const {return state;};
    double getFuel_consuption() const {return fuel_consumption;};
    double getRocket_mass() const {return rocket_mass; }
    Vector3D getThrustForce() const {
        if (state.fuel = 0) return Vector3D(0,0,0);
        return Vector3D(thrust *tx, thrust*ty, thrust*tz);
    }

    




}