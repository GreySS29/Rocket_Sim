#include "iostream"
#include "../include/Gravity_temp.h"
#include "../include/Earth.h"
#include "../include/Tank.h"
#include "../include/Engine.h"
#include "../include/Stage.h"
#include "../include/Payload.h"



int main() {
    Earth earth;  
    Engine engine {earth.surfacePoint(5.0),10000.0,1500000.0, 547.0};
    Tank tank {earth.surfacePoint(10.0), 5000.0,40000.0};
    std::unique_ptr stage = Stage::creat_stage(10.0,engine, tank, earth);
    
  

    const int max_steps = 20; //s 
    double target_height = 100000.0; //m
    const double PACE = 1; //s 
    const double V_ORBITAL = earth.get_orbital_velocity(target_height);
    std::cout << "Target Hight : " << V_ORBITAL << '\n';

    std::cout << "\n=== Начальное состояние ===\n";
    stage->print_status_flight();

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
        stage->launch_stage(earth,PACE);

        if (i % 1 ==0)
        {
            std::cout << "Time: " << PACE*i << '\n';
            stage->print_status_flight();
        }

    }

    std::cout << "\n=== Финальное состояние ===\n";
    stage->print_status_flight();
    return 0;

} 