#include "../include/Rocket.h"
using std::cout;


std::unique_ptr<Rocket> Rocket::create_rocket(std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload& payload, Earth& earth)
{
    std::unique_ptr<Rocket> rocket = std::make_unique<Rocket> (
        earth.surfacePoint(5.0),
        0.3,
        10.0,
        std::move(booster),
        std::move(upper_stage),
        payload
    );
    
    return rocket;
}

void Rocket::print_status() const{
    cout << "Rocket" << '\n' <<
    "Rocket_mass: " << this->get_mass() << '\n';

    cout << "Booster" << '\n';
    booster_->print_status();
    cout << "*****************" << '\n';
    upper_stage_->print_status();
    cout << "*****************" << '\n';
    cout << "Payload" << '\n' <<
    payload_.get_mass() << '\n';
}

void Rocket::launch(const Earth& earth, double pace)
{
    booster_->run_engine(true);

    std::cout << "thrust :" << booster_->get_thrust_force() << '\n'
    << "gravity" <<gravity_vec(*this, earth) << '\n'
    << "drag : " << earth.get_dragForce_vec(*this) <<'\n';


    Vector3D F_total =
        booster_->get_thrust_force() +
        gravity_vec(*this, earth) +
        earth.get_dragForce_vec(*this);

    std::cout << F_total << '\n';

    set_acceleration(F_total);
    booster_->reduce_tank_fuel(pace);
    std::cout<< "accel : " << get_acceleration() << '\n'
    << booster_->get_fuel_mass() << '\n';
}