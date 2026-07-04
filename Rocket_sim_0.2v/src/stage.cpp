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