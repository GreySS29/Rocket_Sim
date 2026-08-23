#pragma once
#include "../Earth.h"
#include "Atmo_layer_isa.h"
#include "Atmo_layer_termosphere.h"
#include <vector>

class Atmosphere {
    public:

    Atmosphere() : temperature(delta<K>(288.15)) {};

    void update(quantity<m> geometric_altitude);
    
    // this is rougly approximation !
    const std::vector<std::pair<quantity<km>,quantity<kg/mol>>> mol_mass {
        {delta<km>(150) , delta<kg/mol>(0.02897)},
        {delta<km>(200) , delta<kg/mol>(0.020)},
        {delta<km>(500) , delta<kg/mol>(0.016)},
        {delta<km>(800) , delta<kg/mol>(0.005)},
    };

    //get
    quantity<K> get_temperature() const { return temperature;};
    void get_status () const {
        std::cout << "temp" << temperature << '\t'
        << "press" << pressure << '\t'
        << "density" << density << '\n';
    }

    private:
    Atmo_layer_isa layer_isa;
    Atmo_layer_termosphere layer_termosphere;
    quantity<K> temperature;
    quantity<Pa> pressure;
    quantity<kg / m3> density;
    
    //double speedOfSound;         // a, m/s

    //for < 86 km 
    quantity<m> get_geopotential_altitude (quantity<m> geometric_altitude) const{
        return (Earth::mean_radius * geometric_altitude) / (Earth::mean_radius + geometric_altitude);}

    void set_density() {
        density = pressure / (Dry_air_specific_gas_constant * temperature);}

    
};