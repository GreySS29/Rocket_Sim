#include "../include/Stage.h"
#include <iomanip>

 std::unique_ptr<Stage> Stage::creat_stage(double position_h, Engine& eng, Tank& t , Earth& earth)
 {
    std::unique_ptr<Stage> stage = std::make_unique<Stage> (
        earth.surfacePoint(position_h),
        0.3,
        10.0,
        std::make_unique<Engine>(eng),
        std::make_unique<Tank>(t)
    );
    return stage;
}



void Stage ::launch_stage(const Earth& earth , double pace)
{
     //std::cout << engine->get_thrust_force()<< "\n";
     std::cout <<"grav_vec" << gravity_vec(*this, earth) << "\n";
     std::cout <<"drag_vec" << earth.get_dragForce_vec(*this)<< "\n";

    if (tank->get_fuel_mass() ==0){
        acceleration = earth.get_dragForce_vec(*this); //falling
    } else{

    
    Vector3D F_total = 
        engine->get_thrust_force()+
        gravity_vec(*this, earth)+
        earth.get_dragForce_vec(*this);

    set_acceleration(F_total);

    double consum = engine->get_fuel_consumption(pace);
    tank->reduce_fuel_mass(consum);
    if(tank->get_fuel_mass() == 0) 
        {
            engine->set_fuel(false);
        };

    this->reduce_mass(consum);
    }
    
    set_velocity(pace);
    update_position(velocity, pace);


    // std::cout<< "*********"<<'\n'
        
       
    //     <<"Tank mass(with fuel):" <<tank->get_mass() <<'\n'
    //     <<"Fuel mass:" << tank->get_fuel_mass() <<'\n'
    //     <<"Stage mass :" << this->get_mass() << '\n'
    //     <<"Position :" << this->get_position() << '\n'
    //     <<"Velocity :" << this->get_velocity() << '\n'
    //     <<"Acceleration :" << this->get_acceleration() << '\n';

}



void Stage::print_status_flight() const{
    std::cout << std::fixed << std::setprecision(2);
        std::cout << "Height: " << this->get_position_above_surface().y << " м( " << this->get_position_above_surface().y/1000.0 << " км)\n";
        std::cout << "Velocity: " << this->get_velocity().magnitude() << " м/с (" <<  this->get_velocity().magnitude()*3.6 << " км/ч)\n";
        std::cout << "Acceleration: " << this->get_acceleration().magnitude() << " м/с \n";
        std::cout << "Mass: " <<this->get_mass() << " кг\n";
        std::cout << "Fuel: " << tank->get_fuel_mass() << " кг\n";
        //std::cout << "Направление : "<<engine->get_thrust_direction() << '\n';
        std::cout << "=========================\n";
}


void Stage::print_status() const {
    std::cout << "=========================\n" 
        <<"Engine_thrust: " <<engine->get_thrust()<<'\n'
        <<"Engine_mass:" <<engine->get_mass()<<'\n'
        <<"Tank mass(with fuel):" <<tank->get_mass() <<'\n'
        <<"Fuel mass:" << tank->get_fuel_mass() <<'\n'
        <<"Stage mass :" << this->get_mass() << '\n'
        <<"Start_position :" << this->get_position_above_surface()<<'\n'
        << "=========================\n";
}