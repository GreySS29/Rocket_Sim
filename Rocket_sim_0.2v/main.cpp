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

    //booster
    Engine engine {earth.surfacePoint(5.0),5000.0,1200000.0, 547.0};
    Tank tank {earth.surfacePoint(10.0), 5000.0,4000.0};
    std::unique_ptr booster = Stage::creat_stage(5.0,engine, tank, earth);

    //upper_stage
    Engine engine_up {earth.surfacePoint(15.0),3000.0,300000.0, 200.0};
    Tank tank_up {earth.surfacePoint(20.0), 1000.0,11000.0};
    std::unique_ptr upper_stage = Stage::creat_stage(15.0,engine_up, tank_up, earth);
    
    
    Payload payload {earth.surfacePoint(25.0),10000, 0.3, 10,{0,300,0}};

    std::unique_ptr rocket = Rocket::create_rocket(std::move(booster),std::move(upper_stage),payload,earth);

    
    rocket->print_status();
    
     const int max_steps = 30;
     const int PACE = 1;
     int last_step = 0;

    //1 stage 0-10 s , 
    rocket->run_engine(true,1);
     for(int step=0; step<=max_steps; ++step)
     {
        double t = step* PACE;
        std::cout << "Time : " << t << " s" << '\n';
        rocket ->launch_booster(earth,t);
        rocket ->update_condition(t);
        
        last_step = t;
     }
    std::cout << "time of separate Booster : " << last_step << '\n';
    std::unique_ptr<Stage> booster_single =rocket->separate_booster();  
    
    rocket->print_status();

    
    return 0;

} 