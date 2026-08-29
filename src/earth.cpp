#include "../include/Earth.h"


double Earth::get_air_density(double height) const {
    if (height >= ATMOSPHERE_HEIGHT) return 0; // approxim .. ?
    return AIR_DENSITY_SURFACE * std::exp(-height/8500); //exp==pow
};



