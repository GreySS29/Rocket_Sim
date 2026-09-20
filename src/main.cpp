#include <iostream>
#include <chrono>
#include "../include/Earth.h"
#include "../include/Rocket.h"
#include "../include/Fabric.h"
#include "../include/Launch_bay.h"
#include "../include/GUI/Display.h"
#include "../include/GUI/RocketRender.h"
#include "../include/GUI/Log.h"
#include "../include/Flight_parameters/Friction_drag.h"
#include "../include/Panel/Server.h"
#include "../include/Panel/Panel_data.h"
#include "../include/Sim_state.h"

int main_s(int argc, char** argv){
    Log log;
    Earth earth;
    Fabric fabric;
    Launch_bay launch_bay;
    RocketRender render;
    
    

    std::unique_ptr<Rocket> rocket = fabric.create_falcon9(earth);
    launch_bay.launch_falcon9(earth,rocket,render,log);


//    std::unique_ptr<Rocket> rocket = fabric.create_def_rock(earth);
//    launch_bay.launch_def_rock(earth,rocket);
        
    
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

        //negative friction force!!!!
        


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
} 


//sudo ss -tlpn | grep :5555   


using Clock = std::chrono::steady_clock;

int main() {


    Panel_data panel_data;
    
    RocketServer server(5555, [](const std::string& cmd){
        // Optional: parse JSON / validate here
        // This runs in session threads; keep it light.
    });

    server.start();


    bool simRunning = true;
    Sim_state state = Sim_state::Base;
    bool abortRequested = false;

    using Clock = std::chrono::steady_clock;
    auto currentTime = Clock::now();
    const double dt = 1.0;
    double accumulator = 0.0;

while (simRunning) {

    std::string cmd;
    while (server.pollCommand(cmd)) {
        panel_data.parse(cmd);

        if (panel_data.launch == 0 && state == Sim_state::Base) {
            std::cout << "launching\n";
            state = Sim_state::Running;
        }

        
        if (panel_data.abort == 0) {
            abortRequested = true;
        }
    }

    
    if (state == Sim_state::Running && abortRequested) {
        std::cout << "aborting\n";
        state = Sim_state::Aborted;
        
    }

    
    if (state == Sim_state::Running) {
        auto newTime = Clock::now();
        double frameTime = std::chrono::duration<double>(newTime - currentTime).count();
        currentTime = newTime;

        if (frameTime > 0.25) frameTime = 0.25;  
        accumulator += frameTime;

        while (accumulator >= dt) {
            
            
            std::cout << " one pace\n";

            // sim.update(dt);

            accumulator -= dt;
        }
    }

    //if it ground ---break

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}
    server.stop();
    return 0;
}