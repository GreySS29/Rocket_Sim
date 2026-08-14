#include "iostream"

#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/Display.h"
#include "../include/GUI/RocketRender.h"
#include "../include/Enviroment/Atmosphere.h"

void m_main(int argc, char** argv){
    Earth earth;
    Fabric fabric;
    Launch_bay launch_bay;
    RocketRender render;
    
    

    std::unique_ptr<Rocket> rocket = fabric.create_falcon9(earth);
    launch_bay.launch_falcon9(earth,rocket,render);

//    std::unique_ptr<Rocket> rocket = fabric.create_def_rock(earth);
//    launch_bay.launch_def_rock(earth,rocket);
        
    //render.print();
    Display display {render};
    Display::instance = &display;
    display.run(argc, argv);


    
}




int main(int argc, char** argv) {
   Earth earth;
   Atmosphere atm;
   atm.temperature = delta<K>(293.15); // ??
   atm.pressure = 101325.0 * Pa;

   auto rho = atm.density();
   quantity<m> geom_al = 34'000 * m;
   atm.set_tempeture(geom_al);
   std::cout << rho << '\n'
   << atm.temperature << '\n' ; 

} 