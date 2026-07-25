#include "../include/Rocket.h"
#include <iomanip>
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

void Rocket::launch_booster(const Earth& earth , double pace)
{
    Vector3D F_total = 
        booster_->run_engine(true)+ // vector thrust_vorce (reduce tank fluel_mass and mass_stage)
        gravity_vec(earth,*this)+
        earth.get_dragForce_vec(*this);
         
         //std::cout <<"grav_vec" << gravity_vec(*this, earth) << "\n";
         //std::cout <<"drag_vec" << earth.get_dragForce_vec(*this)<< "\n";

        //std::cout << "F_total" << F_total << '\n';
        print_status_flight();
        
    set_acceleration(F_total);

    set_velocity(pace);
   
    update_position(velocity_, pace);
    update_mass();
}


void Rocket::print_status_flight() const{
    cout << std::fixed << std::setprecision(2);
        cout << "H: " << this->get_position_above_surface().y << " m( " << this->get_position_above_surface().y/1000.0 << " km)" << '\t' <<
        "V: " << this->get_velocity().magnitude() << " m/s (" <<  this->get_velocity().magnitude()*3.6 << " km/h)" << "||" <<
        "A: " << this->get_acceleration().magnitude() << " m/s2 "<< '\t' <<
        "M: " <<this->get_mass() << " kg" << "||" <<
        "F: " << booster_->get_fuel_mass() << " kg\n";
        //cout << "Направление : "<<get_thrust_direction() << '\n';
        cout << "=========================\n";
}

