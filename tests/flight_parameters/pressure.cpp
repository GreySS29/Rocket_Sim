#include <iostream>
#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/RocketRender.h"
#include "../include/GUI/AtmosphereRender.h"
#include "../include/GUI/Log.h"
#include "../include/Flight_parameters/FrictionDrag.h"
#include "../include/Flight_parameters/PressureDrag.h"




int main() {

    try
    {
        Earth earth;
        FrictionDrag frgrad;
      
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
} 






