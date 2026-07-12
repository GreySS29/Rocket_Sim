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
    Engine engine {earth.surfacePoint(5.0),10000.0,1500000.0, 547.0};
    Tank tank {earth.surfacePoint(10.0), 5000.0,40000.0};
    std::unique_ptr stage = Stage::creat_stage(engine, tank, earth);
    //Payload payload {earth.surfacePoint(10000),10000, 0.3, 10,{0,300,0}};
  
    

    const int max_steps = 10; //s 
    double target_height = 100000.0; //m
    const double PACE = 1; //s 
    const double V_ORBITAL = earth.get_orbital_velocity(target_height);
    std::cout << V_ORBITAL;

    std::cout << "\n=== Начальное состояние ===\n";
    stage->print_status();

    for(int i=0; i<max_steps; ++i)
    {
        if(stage->get_position_above_surface().y > target_height && stage->get_velocity().magnitude() >V_ORBITAL)
        {
            std::cout << "\n*** РАКЕТА ДОСТИГЛА ОРБИТЫ! ***\n";
            break;
        }

        if(stage->get_position_above_surface().y <0 && stage->get_velocity().y <0 && i > 10 ) 
        {
            std::cout << "\n*** РАКЕТА НАЧИНАЕТ ПАДАТЬ ***\n";
            break;
        }  
        stage->launch_stage(earth,PACE*i);

        if (i % 1 ==0)
        {
            std::cout << "Time: " << PACE*i << '\n';
            stage->print_status();
        }

    }

    std::cout << "\n=== Финальное состояние ===\n";
    stage->print_status();
    return 0;

} 