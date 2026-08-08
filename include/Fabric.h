#pragma once
#include "Rocket.h"
#include "Earth.h"


class Fabric {
    public:
    std::unique_ptr<Rocket> create_def_rock (const Earth& earth);
    std::unique_ptr<Rocket> create_falcon9 (const Earth& earth);
};