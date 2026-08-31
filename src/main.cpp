#include "iostream"

#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/Display.h"
#include "../include/GUI/RocketRender.h"
#include "../include/Rocket_components/Flight_parameters.h"
#include "../include/GUI/Log.h"
int main(int argc, char** argv){
    Log log;
    Earth earth;
    Fabric fabric;
    Launch_bay launch_bay;
    RocketRender render;
    
    

    std::unique_ptr<Rocket> rocket = fabric.create_falcon9(earth);
    launch_bay.launch_falcon9(earth,rocket,render,log);


//    std::unique_ptr<Rocket> rocket = fabric.create_def_rock(earth);
//    launch_bay.launch_def_rock(earth,rocket);
        
    // render.print();
    // Display display {render};
    // Display::setInstance(display);
    // display.setAnimationSpeed(10.0);
    // display.run(argc, argv);

    return 0;
    
}


int main_m(int argc, char** argv) {

    try
    {
        Earth earth;
        // Flight_parameters flp(atm);


        // atm.update(56668 *m);
        // atm.get_status();
        // Vector3D vel {1874.8,734.67,0.};

        // // atm.update(19116 *m);
        // // atm.get_status();
        // // Vector3D vel {391.8,513.67,0.};

        // flp.set_real_velocity(vel);
        // flp.set_mach_number();
        // flp.set_dynamic_pressure();
        // flp.set_reynolds_number(70 * m);
        // std::cout<<flp.get_real_velocity() << '\n'
        // <<flp.get_mach_number()<<'\n'
        // <<flp.get_dynamic_pressure() << '\n'
        // <<flp.get_reynolds_number() << '\n';
   

        //quantity<m> altitude = delta<m>(25000);
    // atm.update(altitude);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
} 