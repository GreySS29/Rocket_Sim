#include "iostream"

#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"


int main() {
    Earth earth;
    Fabric fabric;
    Launch_bay launch_bay;
    

    std::unique_ptr<Rocket> rocket = fabric.create_falcon9(earth);
    launch_bay.launch_falcon9(earth,rocket);

//    std::unique_ptr<Rocket> rocket = fabric.create_def_rock(earth);
//    launch_bay.launch_def_rock(earth,rocket);
   


    return 0;

} 