#pragma once
#include "Fabric.h"
#include <fstream>

class Launch_bay {

    public:
    void launch_falcon9(Earth& earth, std::unique_ptr<Rocket>& rocket );
    void launch_def_rock(Earth& earth,std::unique_ptr<Rocket>& rocket);

};

