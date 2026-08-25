#include "../../include/Enviroment/Atmosphere.h"

void Atmosphere::update(quantity<m> geometric_altitude){
    
        quantity isa_boundary = delta<m>(86'000);
        quantity termpsphere_boundary = delta<m>(500'000); // temporary
        quantity exosprhehe_boundary = delta<m>(1'000'000); // not specifically

        molar_mass = get_atmo_mol_mass(geometric_altitude);

        if(geometric_altitude < 0 * m){
        throw std::domain_error("Negative geopotential altitude");}
        else if (geometric_altitude <= isa_boundary){

            const quantity<m> geopot_altitude = get_geopotential_altitude(geometric_altitude);
            size_t layer = layer_isa.find_layer(geopot_altitude);
            std::cout<< layer<< '\n';

            temperature = layer_isa.compute_temperature(layer,geopot_altitude);
            pressure = layer_isa.compute_pressure(layer,temperature,geopot_altitude);
            set_density();
     
        } 
        else if (geometric_altitude<=termpsphere_boundary){
            
            temperature = layer_termosphere.compute_temperature(geometric_altitude);
            pressure = layer_termosphere.compute_pressure(geometric_altitude,temperature,molar_mass);
            set_density();
        }
        else if (geometric_altitude<exosprhehe_boundary){
            std::cerr << "Not func exosphere";
        }
        else std::cerr << "Not correct function was used";
    };


    void Atmosphere::get_status () const {
        std::cout << "temp" << temperature << '\t'
        << "press" << pressure << '\t'
        << "density" << density << '\t'
        << "molar_mass" << molar_mass << '\n';
    }


    const quantity<kg/mol> Atmosphere::get_atmo_mol_mass(const quantity<km> geometric_altitude){
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

   