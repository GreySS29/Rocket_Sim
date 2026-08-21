#pragma once
#include "../Earth.h"
#include "Atmo_layer_isa.h"
#include "Atmo_layer_termosphere.h"






class Atmosphere {
    public:

    Atmosphere() : temperature(delta<K>(288.15)) {};

    void set_tempeture(quantity<m> geometric_altitude);
    

    //get
    quantity<K> get_temperature() const { return temperature;};

    private:
    Atmo_layer_isa layer_isa;
    Atmo_layer_termosphere layer_termosphere;
    quantity<K> temperature;
    quantity<Pa> pressure;
    quantity<kg / m3> density() const {
        constexpr auto R_air                  = 287.05 * J / (kg * K);
        return pressure / (R_air * temperature);}
    //double speedOfSound;         // a, m/s

    //for < 86 km 
    quantity<m> get_geopotential_altitude (quantity<m> geometric_altitude) const{
        return (Earth::mean_radius * geometric_altitude) / (Earth::mean_radius + geometric_altitude);}




    
};