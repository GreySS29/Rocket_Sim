#pragma once
#include "Fabric.h"
#include <fstream>
#include "GUI/Log.h"
#include <vector>
#include "GUI/RocketRender.h"

class Launch_bay {

    public:
    void launch_falcon9(Earth& earth, std::unique_ptr<Rocket>& rocket ,RocketRender&, Log& log);
    void launch_falcon9_from_panel(Earth& earth, std::unique_ptr<Rocket>& rocket,RocketRender& roc_render, auto PACE , int angle){
        rocket ->set_direction(angle);
        rocket ->run(earth,PACE, roc_render);
        //rocket ->print_status_flight_short();
    };
    void launch_def_rock(Earth& earth,std::unique_ptr<Rocket>& rocket,RocketRender&);
};

