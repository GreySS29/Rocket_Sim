#include "../include/Rocket.h"

using std::cout;


std::unique_ptr<Rocket> Rocket::create_rocket(std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload payload, const Earth& earth)
{
    std::unique_ptr<Rocket> rocket = std::make_unique<Rocket> (
        std::move(booster),
        std::move(upper_stage),
        payload
    );
    
    return rocket;
}



void Rocket::run(const Earth& earth , double pace)
{
    Vector3D F_total = 
        active()->run_engine(true)+ // vector thrust_vorce (reduce tank fluel_mass and mass_stage)
        gravity_vec(earth,*this)+
        
        earth.get_dragForce_vec(active());
         
        //  std::cout <<"grav_vec" << gravity_vec(*this, earth) << "\n";
        //  std::cout <<"drag_vec" << earth.get_dragForce_vec(active())<< "\n";

        // std::cout << "F_total" << F_total << '\n';
       // print_status_flight_short();
        
    active()->set_acceleration(F_total, get_mass());

    active()->set_velocity(pace);
    Vector3D vel = active()->get_velocity();
    active()->update_position(vel, pace);
  
}



void Rocket::print_status() const{
    cout << "Rocket" << '\n' <<
    "Rocket_mass: " << get_mass() << '\n' <<
    "Position: " << active()->get_position_above_surface()<<'\n'<<
    "Acceleration: " << active()->get_acceleration().magnitude() << " m/sec2 \n" <<
    "Velocity: " << active()->get_velocity().magnitude() << " m/sec (" 
    << active()->get_velocity().magnitude()*3.6 << " km/h)\n";

    if(booster_!=nullptr) {
        cout << "Booster" << '\n';
        booster_->print_status();
    }
    
 
    cout << "Upper_stage" << '\n';
    upper_stage_->print_status();
    
    cout << "Payload" << '\n' <<
    payload_.get_mass() << '\n';
   
    
}
// void Rocket::print_status_flight() const{
//     cout << std::fixed << std::setprecision(2);
//         cout << "H: " << this->get_position_above_surface().y << " m( " << this->get_position_above_surface().y/1000.0 << " km)" << '\t' <<
//         "V: " << this->get_velocity().magnitude() << " m/s (" <<  this->get_velocity().magnitude()*3.6 << " km/h)" << "||" <<
//         "A: " << this->get_acceleration().magnitude() << " m/s2 "<< '\t' <<
//         "M: " <<this->get_mass() << " kg" << "||" <<
//         "F: " << booster_->get_fuel_mass() << " kg\n";
//         //cout << "Направление : "<<get_thrust_direction() << '\n';
//         cout << "=========================\n";
// }

void Rocket::print_status_flight_short() const{
     std::cout << std::fixed << std::setprecision(2);
        std::cout << "H: " << active()->get_position_above_surface().y << " m "  << '\t' <<
        "V: " << active()->get_velocity() << " m/s " <<  "||" <<
        "A: " << active()->get_acceleration() << " m/s2 "<< "||" <<
        //"D: "<< booster_->get_thrust_direction() << '\n'<<
        "M: " <<get_mass() << " kg" << "||" ;
        //"F: " << booster_ ->get_fuel_mass() << " kg\n";
        std::cout << "=========================\n";
}

void Rocket::print_status_flight_short(std::ofstream& ofs , int time) const{
        ofs << std::fixed << std::setprecision(2);
        ofs << "Time : " << time <<  "  |" <<
        "H: " << active()->get_position_above_surface().y << " m "  << '\t' <<
        "V: " << active()->get_velocity().magnitude() << " m/s " <<  "/" <<
        active()->get_velocity()<< "||"
        "A: " << active()->get_acceleration().magnitude() << " m/s2 "<< "/" <<
        active()->get_acceleration() << "||" <<
        "D: "<< active()->get_thrust_direction() << '\n'<<
        "M: " <<get_mass() << " kg" << "||"  <<
        "F: " << active() ->get_fuel_mass() << " kg\n" <<
        "=========================\n";
}

// std::ofstream& operator<<(std::ofstream& ofs, const Rocket& rocket){
//     ofs << rocket.print_status_flight_short();

// }
