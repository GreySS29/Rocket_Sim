#include "../include/Stage.h"

 std::unique_ptr<Stage> Stage::creat_stage(Engine& eng, Tank& t , Earth& earth)
 {
    std::unique_ptr<Stage> stage = std::make_unique<Stage> (
        earth.surfacePoint(10000.0),
        std::make_unique<Engine>(eng),
        std::make_unique<Tank>(t)
    );
    std::cout<<"Engine_thrust: " <<eng.get_thrust()<<'\n'
        <<"Engine_mass:" <<eng.get_mass()<<'\n'
        <<"Tank mass(with fuel):" <<t.get_mass() <<'\n'
        <<"Fuel mass:" << t.get_fuel_mass() <<'\n'
        <<"Stage mass :" << stage->get_mass() << '\n'
        <<"Start_position :" << stage->get_position() << '\n';
    return stage;
}



void Stage ::launch_stage(const Earth& earth, const Payload& payload)
{
    // std::cout << engine->get_thrust_force()<< "\n";
    // std::cout << gravity_vec(*this, earth) << "\n";
    // std::cout << earth.get_dragForce_vec(payload)<< "\n";
    Vector3D F_total = 
        engine->get_thrust_force()+
        gravity_vec(*this, earth)+
        earth.get_dragForce_vec(payload);

    set_acceleration(F_total);
    // std::cout << acceleration;

    double consum = engine->get_fuel_consumption() * PACE;
    tank->reduce_fuel_mass(consum);
    if(tank->get_fuel_mass() <0) 
    {
        tank->set_fuel_mass(0); 
        engine->set_fuel(false);
    };
    this->reduce_mass(consum);

    std::cout<< "****Launch*****"<<'\n'
        
       
        <<"Tank mass(with fuel):" <<tank->get_mass() <<'\n'
        <<"Fuel mass:" << tank->get_fuel_mass() <<'\n'
        <<"Stage mass :" << this->get_mass() << '\n'
        <<"Start_position :" << this->get_position() << '\n';

}