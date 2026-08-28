#include "iostream"

#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/Display.h"
#include "../include/GUI/RocketRender.h"
#include "../include/Enviroment/Atmosphere.h"
#include "../include/Enviroment/Atmo_layer_termosphere.h"
#include "../include/Enviroment/Atmo_layer_isa.h"

int main(int argc, char** argv){
    Earth earth;
    Atmosphere atm;
    Fabric fabric;
    Launch_bay launch_bay;
    RocketRender render;
    
    

    std::unique_ptr<Rocket> rocket = fabric.create_falcon9(earth);
    launch_bay.launch_falcon9(earth,rocket,render);



    std::ofstream ofs("../Log/atm.txt");

        if (!ofs.is_open()) {
            std::cout << "log doesn't exist\n";
            
        }
    
    for (size_t i =0; i< render.trajectory.size(); ++i){
        quantity<m> all = render.trajectory[i].second * m;
        atm.update(all);
        atm.print_to_log(ofs,all);
    }

//    std::unique_ptr<Rocket> rocket = fabric.create_def_rock(earth);
//    launch_bay.launch_def_rock(earth,rocket);
        
    //render.print();
    Display display {render};
    Display::setInstance(display);
    display.setAnimationSpeed(10.0);
    display.run(argc, argv);

    return 0;
    
}


int main_m(int argc, char** argv) {
   Earth earth;
   Atmosphere atm;
   Atmo_layer_isa isa;
   Atmo_layer_termosphere term;
   

    quantity<m> altitude = delta<m>(25000);
    atm.update(altitude);
   
    
    
  
    

    


} 