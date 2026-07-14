#include "iostream"
#include "include/Gravity_temp.h"
#include "include/Earth.h"
#include "include/Tank.h"
#include "include/Engine.h"
#include "include/Stage.h"
#include "include/Payload.h"
#include "include/Rocket.h"


int main() {
    Earth earth;

    Engine engine {earth.surfacePoint(5.0),10000.0,1500000.0, 547.0};
    Tank tank {earth.surfacePoint(10.0), 5000.0,40000.0};
    std::unique_ptr booster = Stage::creat_stage(engine, tank, earth);


    Engine engine_up {earth.surfacePoint(15.0),5000.0,300000.0, 200.0};
    Tank tank_up {earth.surfacePoint(20.0), 1000.0,15000.0};
    std::unique_ptr upper_stage = Stage::creat_stage(engine_up, tank_up, earth);
    
    
    Payload payload {earth.surfacePoint(25.0),10000, 0.3, 10,{0,300,0}};

    std::unique_ptr rocket = Rocket::create_rocket(std::move(booster),std::move(upper_stage),payload,earth);

    
    rocket->print_status();
  
    

    
    return 0;

} 