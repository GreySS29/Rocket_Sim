#include "../../include/Enviroment/Atmosphere.h"


//mass_mol-> temperature->pressure->density->sonic_vel
void Atmosphere::update(quantity<m>& geometric_altitude){
        set_atmo_mol_mass(geometric_altitude);
        set_temperature_pressure(geometric_altitude);
        set_viscosity();
        set_density();
        set_sonic_velosity();
    }

    void Atmosphere::set_atmo_mol_mass(const quantity<km> geometric_altitude){
        if(geometric_altitude < mol_mass[0].first) {
                    molar_mass =  mol_mass[0].second;
                    return;}
        if(geometric_altitude > mol_mass.back().first) {
                    molar_mass = 0 * kg/mol ;
                    std::cout<< "molar mass > 800 km is 0 kg/mol ";
                    return;}
        for (size_t i =0; i < mol_mass.size()-1; ++i)
        {
            if (geometric_altitude > mol_mass[i].first && geometric_altitude < mol_mass[i+1].first )
            {
                    const auto dm = mol_mass[i+1].second - mol_mass[i].second;
                    const auto dh = mol_mass[i+1].first-mol_mass[i].first;
                    const auto dz = geometric_altitude - mol_mass[i].first;
                    molar_mass =  mol_mass[i].second + (dm/dh) * dz;
                    break;
            }
        } 
    }

    void Atmosphere::set_temperature_pressure(quantity<m>& geometric_altitude){
        quantity isa_boundary = atmo_layers.back().base_altitude;
        quantity termpsphere_boundary = delta<m>(500'000); // temporary
        quantity exosprhehe_boundary = delta<m>(1'000'000); // not specifically

        if(geometric_altitude < 0 * m){
            throw std::domain_error("Negative geopotential altitude");}
            else if (geometric_altitude <= isa_boundary){
                const quantity<m> geopot_altitude = get_geopotential_altitude(geometric_altitude);
                size_t layer = layer_isa.find_layer(geopot_altitude);
                temperature = layer_isa.compute_temperature(layer,geopot_altitude);
                pressure = layer_isa.compute_pressure(layer,temperature,geopot_altitude,molar_mass);
            } 
            else if (geometric_altitude<=termpsphere_boundary){
                temperature = layer_termosphere.compute_temperature(geometric_altitude);
                pressure = layer_termosphere.compute_pressure(geometric_altitude,temperature,molar_mass);
            }
            else if (geometric_altitude<exosprhehe_boundary){
                std::cerr << "Not func exosphere";
            }
            else std::cerr << "Not correct function was used";

    }

     void Atmosphere::set_sonic_velosity () {
        double heat_capacity_ratio = 1.4; 
        
        if (temperature > delta<K>(300) && temperature < delta<K>(3000)) {
            double t_k = temperature.numerical_value_in(mp_units::si::kelvin);
            heat_capacity_ratio = 1.4 - 0.1*((t_k - 300)/2700);
            std::cout << "HCR" << heat_capacity_ratio<<'\n';
        }
        sonic_velosity =  mp_units::sqrt(heat_capacity_ratio*pressure/density); 
    }

    void Atmosphere::set_viscosity() { 
        quantity<K> t_base = delta<K>(273.15);
        quantity<K> sutherland_const = delta<K>(110.4);
        quantity<Pa*s> v_base = 1.716e-5 * Pa*s;

        const auto comp1 =  mp_units::pow<3,2>(temperature / t_base); 
        const auto comp2 = (t_base + sutherland_const) / (temperature+sutherland_const);
        viscosity = v_base * comp1 *comp2;
    }



    void Atmosphere::get_status () const {
        std::cout << "temp: " << temperature << '\t'
        << "press: " << pressure << '\t'
        << "dens: " << density << '\t'
        << "molar_mass: " << molar_mass << '\n'
        << "viscosity: " << viscosity << '\t'
        << "super_sonic: " << sonic_velosity << '\t'
        << "wind_vel: " << wind_velosity << '\n';
    }

    void Atmosphere::print_to_log(std::ofstream&ofs, quantity<m>& geometric_altitude) const{
        ofs << std::fixed << std::setprecision(2);
        ofs << "Alt: " << geometric_altitude << " | "
        <<"T: " << temperature << " | "
        << "P: " << pressure << " | "
        << "D: " << density << " | "
        << "M: " << molar_mass << " | "
        << "Visc: " << viscosity << " | "
        << "V_a: " << sonic_velosity << " | "
        << "V_w: " << wind_velosity << '\n';
    }