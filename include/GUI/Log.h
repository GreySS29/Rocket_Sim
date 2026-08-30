#pragma once
#include <fstream>
#include <iostream>

struct Log {
    std::ofstream ofs_flight{"../Log/log.txt"};
    std::ofstream ofs_force{"../Log/force.txt"};
    std::ofstream ofs_atmo{"../Log/atm.txt"};

    Log() {
        if (!ofs_flight.is_open()) std::cerr << "flight: not open\n";
        if (!ofs_force.is_open())  std::cerr << "force: not open\n";
        if (!ofs_atmo.is_open())   std::cerr << "atmo: not open\n";
    }
};