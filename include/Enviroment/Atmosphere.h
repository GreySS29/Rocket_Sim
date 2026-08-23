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

    // This is a simple template for calculating the molar mass  of the atmosphere in each layer up to an altitude of 500 km
    // quation: piecewise linear approximation
    const quantity<kg/mol> get_atmo_mol_mass(const quantity<km> geometric_altitude){
        for (size_t i =0; i < mol_mass.size()-1; ++i)
        {
            if (geometric_altitude < mol_mass[i].first)
            {
                if(i==0) return mol_mass[0].second;
                else 
                {
                    const auto dm = mol_mass[i+1].second - mol_mass[i].second;
                    const auto dh = mol_mass[i+1].first-mol_mass[i].first;
                    const auto dz = geometric_altitude - mol_mass[i].first;
                    return mol_mass[i].second + (dm/dh) * dz;
                }
            }
        } 
        return delta<kg/mol> (0); // for compile warning 
    }

    //get
    quantity<K> get_temperature() const { return temperature;};
    void get_status () const {
        std::cout << "temp" << temperature << '\t'
        << "press" << pressure << '\t'
        << "density" << density << '\t'
        << "molar_mass" << molar_mass << '\n';
    }

    private:
    Atmo_layer_isa layer_isa;
    Atmo_layer_termosphere layer_termosphere;
    quantity<K> temperature;
    quantity<Pa> pressure;
    quantity<kg / m3> density;
    quantity<kg/mol> molar_mass;
    
    //double speedOfSound;         // a, m/s

    //for < 86 km 
    quantity<m> get_geopotential_altitude (quantity<m> geometric_altitude) const{
        return (Earth::mean_radius * geometric_altitude) / (Earth::mean_radius + geometric_altitude);}

    void set_density() {
        density = pressure*molar_mass / (Gaz_constant * temperature);}

    
};