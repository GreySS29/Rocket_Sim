#include "Enviroment.h"
#include "Rocket.h"
#include <math.h>

double Enviroment::getAirDensity(double height) const 
{
    if (height >= ATMOSPHERE_HEIGHT) return 0; // типо равно нулю при 100 км?
    return AIR_DENSITY_SURFACE * std::exp(-height/8500); //exp==pow
}

Vector3D Enviroment::getGravityForce(const Rocket& rocket) const
{
    RocketState& state = rocket.getState();
    double r = EARTH_RADIUS + state.position.y;
    double g = GRAVITY * (EARTH_RADIUS/r) * (EARTH_RADIUS/r);
    return Vector3D(0, -g*state.mass,0);
}

Vector3D Enviroment::getDragForce(const Rocket& rocket) const 
{
    RocketState& state = rocket.getState();
    double density = get_AirDensity(state.position.y);
    if (density ==0) return Vector3D(0,0,0);
    double v = state.velocity.magnitude();
    double drag = 0.5 * density * v * v * C_D * AREA;
    return state.velocity.normalize() - (-drag);
}

void Enviroment::step(Rocket& rocket) 
{
    RocketState& state = rocket.getState();
    if (state.fuel ==0) {
        state.acceleration = getGravityForce(rocket) / state.mass;
    }
    else {
        Vector3D F_thrust = rocket.getThrustForce();
        Vector3D F_gravity = getGravityForce(rocket);
        Vector3D F_drag = getDragForce(rocket);

        Vector3D F_total = F_thrust+F_gravity+F_drag;
        state.acceleration = F_total/ state.mass;

        state.fuel -= rocket.getFuel_consuption() *PACE;
        if(state.fuel <0) state.fuel = 0; // wtf?
        state.mass = rocket.getRocket_mass() + state.fuel;
    }

    state.velocity = state.velocity + state.acceleration * PACE;
    state.position = state.position + state.velocity * PACE;
    state.time +=PACE;
}






