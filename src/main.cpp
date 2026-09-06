#include "iostream"

#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/Display.h"
#include "../include/GUI/RocketRender.h"
#include "../include/GUI/Log.h"
#include "../include/Flight_parameters/Friction_drag.h"
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
        Friction_drag frd; 
        //  14 km - falcon 9  
        // const quantity<one> reyn = 591480423.51;
        // const quantity<one> mach = 1.75;
        // const quantity<kg/m3> density = 0.23 * kg/m3;
        // const quantity<m/s> velocity = 516.07 * m/s;
        // const quantity<m2> a_wet = 846 * m2;
        // frd.set_prop_coeff(reyn);
        // frd.set_Fl_M(mach);
        // frd.set_Ft_M(mach);
        // frd.set_skin_friction_coefficient(reyn);
        // frd.set_friction_drag(density,velocity,a_wet);
        // std::cout<<frd.get_prop_coeff()<<'\n'
        // << "Fl_M :" << frd.get_Fl_M() <<'\n'
        // << "Ft_M :" << frd.get_Ft_M() <<'\n'
        // << "skin coef : " << frd.get_skin_friction_coefficient() << '\n'
        // << "friction_drag : " << frd.get_friction_drag() << '\n';
        


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
} 