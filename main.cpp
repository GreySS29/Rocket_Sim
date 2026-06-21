#include "include/Environment.h"
#include "include/Rocket.h"
#include "include/Display.h"


int main ()
{
    Enviroment env;
    Display disp;
    Rocket falcon9 (54900.0,47000.0,1500000.0,500.0);
    
  
    int max_steps = 4000; 

    std::cout << "\n=== Начальное состояние ===\n";
    std::cout << "V_ORBITEL" << V_ORBITAL;
    disp.printStatus(falcon9);

    for(int i = 0; i <max_steps; ++i)
    {
        
        if(falcon9.getState().position.y > TARGET_HEIGHT && falcon9.getState().velocity.magnitude() > V_ORBITAL*0.9)
        {
            std::cout << "\n*** РАКЕТА ДОСТИГЛА ОРБИТЫ! ***\n";
            break;
        }

        if (falcon9.getState().position.y < 0 && falcon9.getState().velocity.y < 0 && i > 10) {
            std::cout << "\n*** РАКЕТА НАЧИНАЕТ ПАДАТЬ ***\n";
            break;
        }
        env.step(falcon9);

        if (i % 500 ==0) 
        {
            disp.printStatus(falcon9);
            std::cout<<falcon9.getState().position.y << '\n';
        }
        
    }

    std::cout << "\n=== Финальное состояние ===\n";
    disp.printStatus(falcon9);
    return 0;

}