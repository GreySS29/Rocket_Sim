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
    Engine engine {earth.surfacePoint(5),10000,1500000,500};
    Tank tank {earth.surfacePoint(10), 5000,40000};
    std::unique_ptr stage = Stage::creat_stage(engine, tank, earth);
    Payload payload {earth.surfacePoint(10000),10000,{0,300,0}};
  
    stage->launch_stage(earth, payload);
    

    
    return 0;
} 