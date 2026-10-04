#pragma once
#include "Fabric.h"
#include <fstream>
#include "GUI/Log.h"
#include <vector>
#include "GUI/RocketRender.h"
#include "GUI/ExDataGUI.h"

class Launch_bay {

    public:
    void launch_falcon9(Earth& earth, std::unique_ptr<Rocket>& rocket ,RocketRender&, Log& log);
    void launch_falcon9_from_panel(Earth& earth, std::unique_ptr<Rocket>& rocket,RocketRender& roc_render, auto PACE , int angle , ExDataGUI& exdata){
        if (!roc_render.separating) // bad idea temp 
        {
            if (rocket->booster_tank()) {
                std::unique_ptr<Stage> booster_single = rocket->separate_booster(); 
                roc_render.separating = true;
            }
        }
        rocket ->set_direction(angle);
        rocket ->run(earth,PACE, roc_render);
        roc_render.add_angle(angle);
        exdata.set_data(rocket->get_position_above_face().y , rocket->get_position_above_face().x ,rocket->get_velocity().magnitude(),rocket->get_mass(), angle);
        //rocket ->print_status_flight_short();
    };
    void launch_def_rock(Earth& earth,std::unique_ptr<Rocket>& rocket,RocketRender&);
};

