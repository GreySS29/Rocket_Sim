#include "include/Enviroment.h"
#include "include/Rocket.h"
#include "include/Display.h"


int main ()
{
    Enviroment env;
    Display disp;
    Rocket rocket(100000.0,90000.0);
  
    int max_steps = 2000;

    for(int i = 0; i <max_steps; ++i)
    {
        env.step(rocket);
        if (i % 10 ==0) disp.printStatus(rocket);

        const RocketState& s = rocket.getState();
       
        if(s.position.y > 200000 && s.velocity.magnitude() > V_ORBITAL*0.9)
        {
            std::cout << "\n*** РАКЕТА ДОСТИГЛА ОРБИТЫ! ***\n";
            break;
        }

        if (s.position.y < 0 && s.velocity.y < 0 && i > 10) {
            std::cout << "\n*** РАКЕТА НАЧИНАЕТ ПАДАТЬ ***\n";
            break;
        }
    }

    std::cout << "\n=== Финальное состояние ===\n";
    disp.printStatus(rocket);
    return 0;

}