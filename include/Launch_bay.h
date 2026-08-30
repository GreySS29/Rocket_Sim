#pragma once
#include "Fabric.h"
#include <fstream>
#include "GUI/Log.h"
#include <vector>
#include "GUI/RocketRender.h"

class Launch_bay {

    public:
    void launch_falcon9(Earth& earth, std::unique_ptr<Rocket>& rocket ,RocketRender&, Log& log);
    void launch_def_rock(Earth& earth,std::unique_ptr<Rocket>& rocket,RocketRender&);
};

