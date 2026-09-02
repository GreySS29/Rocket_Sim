#include "iostream"

#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/Display.h"
#include "../include/GUI/RocketRender.h"
#include "../include/GUI/Log.h"
#include "../include/Flight_parameters/Skin_drag.h"
int main_m(int argc, char** argv){
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


int main(int argc, char** argv) {

    try
    {
        Earth earth;
        Skin_drag skg;
        const quantity<one> reyn = 600000.;
        skg.set_laminar_flow_fraction(reyn);
        std::cout<<skg.get_laminar_flow_fraction()<<'\n';
        


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
} 