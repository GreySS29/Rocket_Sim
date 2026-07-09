#include "iostream"
#include "include/Gravity_temp.h"
#include "include/Earth.h"
#include "include/Tank.h"
#include "include/Engine.h"
#include "include/Stage.h"
#include "include/Payload.h"



int main() {
    Earth earth;
    // for (double i = 0; i < 100000.0; i+=10000.0)
    // {
    //     Engine engine {20000,100,earth.surfacePoint(i), 50};
    //     //Tank tank {earth.surfacePoint(i),20.0,0};
    //     double s = gravity_magnitude (earth, engine);
    //     std::cout << s << '\n';
    // }   
    Engine engine {20000.0,100.0,earth.surfacePoint(2), 50.0};
    Tank tank {earth.surfacePoint(10), 50,20};
    std::unique_ptr stage = Stage::creat_stage(engine, tank, earth);
    Payload payload {earth.surfacePoint(10000),10,{0,300,0}};
    
    stage->set_velocity(0.5);
    std::cout<<stage->get_velocity();
    
    return 0;
} 