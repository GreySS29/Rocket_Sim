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
    "Rocket_mass: " << get_mass() << '\n' <<
    "Position: " << get_position_above_surface()<<'\n'<<
    "Acceleration: " << get_acceleration().magnitude() << " m/sec2 \n" <<
    "Velocity: " << get_velocity().magnitude() << " m/sec (" 
    << get_velocity().magnitude()*3.6 << " km/h)\n";

    if(booster_!=nullptr) {
        cout << "Booster" << '\n';
        booster_->print_status();
    }
    
 
    cout << "Upper_stage" << '\n';
    upper_stage_->print_status();
    
    cout << "Payload" << '\n' <<
    payload_.get_mass() << '\n';
   
    
}

