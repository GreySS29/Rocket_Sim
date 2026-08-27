#pragma once
#include "../Constants.h"


class Atmo_layer_termosphere
{
    public:
    //profile Bates–Jacchia  T(z) = T_e - (T_e - To) exp [ - (z-zo) / H_t ]
    quantity<K> compute_temperature (quantity<km> geometric_altitude) {
        quantity<K> T_e = get_exospheric_temp();
        quantity<km> H_t = get_H_t();
        const auto exponent = - (geometric_altitude - z_base) / H_t ; 
        return T_e - (T_e - temp_z_base) * mp_units::exp(exponent);
    }
    
    //P = Pb exp ( -g* M*(h-h_b) / R*Tb)
    quantity<Pa> compute_pressure (quantity<km> geometric_altitude, quantity<K> temperature, 
        const auto& mol_mass){
        
        const auto h_base = atmo_layers.back().base_altitude;
        const auto dh = (geometric_altitude - h_base);
        const auto exponent = - ((Standard_gravity *  mol_mass * dh) / (Gaz_constant*temperature));

        return layer_base_press.back() * mp_units::exp(exponent);
    }

    

    private:
    // data from Jacchia-70/71
    const quantity<km> z_base = delta<km>(86);  
    const quantity<K> temp_z_base = delta<K>(186.87); 

    // reverse temperature gradient : Ht = 1 / 0.0291 exp [(T_e - 500) / 1300 ] km
    constexpr quantity<km> get_H_t(){ 
        const auto exponent  = (get_exospheric_temp() - delta<K>(500))/ (delta<K>(1300));
        return  1.0/0.0291 *km * mp_units::exp(exponent); 
    }

    //very rough calculation . F10.7(F) quantities was chosen roughly too. 
    //T_e = 383 + 3.32\,\bar F_{10.7} + 1.8\,(F_{10.7}-\bar F_{10.7}),(Jacchia-70/71, CIRA) 
    constexpr quantity<K> get_exospheric_temp(){
    constexpr double F     = 150.0;
    constexpr double F_mid = 100.0;
    constexpr double T_c_val = 383.0 + 3.32 * F_mid + 1.8 * (F - F_mid);
    constexpr quantity<K> T_c     = delta<K>(T_c_val);
    constexpr quantity<K> T_const = delta<K>(75);
    constexpr quantity<K> T_i     = T_c + T_const;
    return T_i;
    }

};

