#pragma once
#include "../Earth.h"
#include "Atmo_layer_isa.h"






class Atmosphere {
    public:

    Atmosphere() : temperature(delta<K>(288.15)) {};

    void set_tempeture(quantity<m> geometric_altitude);

    //get
    quantity<K> get_temperature() const { return temperature;};

    private:
    Atmo_layer_isa atmo_layer;
    quantity<K> temperature;
    quantity<Pa> pressure;
    quantity<kg / m3> density() const {
        constexpr auto R_air                  = 287.05 * J / (kg * K);
        return pressure / (R_air * temperature);}
    //double speedOfSound;         // a, m/s

    quantity<m> get_geopotential_altitude (quantity<m> geometric_altitude) const{
        return (Earth::mean_radius * geometric_altitude) / (Earth::mean_radius + geometric_altitude);}




    
};