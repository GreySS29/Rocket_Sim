#pragma once
#include "../Earth.h"
#include "Atmo_layer_isa.h"
#include "Atmo_layer_termosphere.h"
#include <vector>
#include "../Vec3_mp.h"






class Atmosphere {

    public:

    Atmosphere() : temperature(Sea_level_temperature), pressure(Sea_level_pressure) {};
    void update(quantity<m> geometric_altitude);
    
    //get
    quantity<K> get_temperature() const { return temperature;};
    void get_status () const;

    
    private:
    Atmo_layer_isa layer_isa;
    Atmo_layer_termosphere layer_termosphere;
    quantity<K> temperature;
    quantity<Pa> pressure;
    quantity<kg / m3> density;
    quantity<kg/mol> molar_mass;
    quantity<m/s> sonic_velosity;
    VelocityVec wind_velosity = make_vec<isq::velocity, m / s>(0., 0., 0.);
    quantity<Pa*s> viscosity;


    // this is rougly approximation !
    const std::vector<std::pair<quantity<km>,quantity<kg/mol>>> mol_mass {
        {delta<km>(150) , delta<kg/mol>(0.02897)},
        {delta<km>(200) , delta<kg/mol>(0.020)},
        {delta<km>(500) , delta<kg/mol>(0.016)},
        {delta<km>(800) , delta<kg/mol>(0.005)},
    };

    //for < 86 km 
    quantity<m> get_geopotential_altitude (quantity<m> geometric_altitude) const{
        return (Earth::mean_radius * geometric_altitude) / (Earth::mean_radius + geometric_altitude);}

        
    void set_density() {
        density = pressure*molar_mass / (Gaz_constant * temperature);}
    void set_sonic_velosity ();

    // This is a simple template for calculating the molar mass  of the atmosphere in each layer up to an altitude of 500 km
    // quation: piecewise linear approximation
    // M1 + ((M2-M1) / (z2-z1)) * (z-z1)
    void set_atmo_mol_mass(const quantity<km> geometric_altitude);
    void set_viscosity() {
        quantity<K> t_base = delta<K>(273.15);
        quantity<K> sutherland_const = delta<K>(110.4);
        quantity<Pa*s> v_base = 1.716e-5 * Pa*s;

        const auto comp1 =  mp_units::pow<3,2>(temperature / t_base); 
        const auto comp2 = (t_base + sutherland_const) / (temperature+sutherland_const);
        viscosity = v_base * comp1 *comp2;
    }
    

    
};