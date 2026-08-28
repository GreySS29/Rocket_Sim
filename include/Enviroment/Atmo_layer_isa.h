#pragma once
#include "../Constants.h"
#include <array>


struct Atmo_layer_isa {

    inline const size_t find_layer (quantity<m> geopot_al);  
    inline const quantity<K> compute_temperature (const size_t layer, const quantity<m> geopot_al);
    inline const quantity<Pa> compute_pressure(const size_t layer,quantity<K>& temperature, const quantity<m> geopot_al,const quantity<kg/mol> molar_mass );
    inline void print_layer_temp_press ();
    
    quantity<m> base_altitude;
    quantity<K/m> lapse_rate;
};


inline constexpr std::array<Atmo_layer_isa, 8> atmo_layers = {{
    {      0 * m, delta<K/m>(-0.0065)  },  // troposphere
    { 11'000 * m, delta<K/m>( 0.0)    },  // tropopause
    { 20'000 * m, delta<K/m>( 0.001)  },  // lower_stratosphere
    { 32'000 * m, delta<K/m>( 0.0028) },  // stratosphere
    { 47'000 * m, delta<K/m>( 0.0)    },  // stratopause
    { 51'000 * m, delta<K/m>(-0.0028) },  // mesosphere
    { 71'000 * m, delta<K/m>(-0.002)  },  // upper_mesosphere
    { 84'852 * m, delta<K/m>(-0.002)} , 

}};

//Tb + L(H-Hb)
inline constexpr  std::array<quantity<K>, atmo_layers.size()> layer_base_temp = []{
    std::array<quantity<K>, atmo_layers.size()> temps{};
        temps[0] = Sea_level_temperature;
        for (size_t i = 1; i < atmo_layers.size(); ++i) {
            const auto& prev = atmo_layers[i - 1];
            const auto dh = atmo_layers[i].base_altitude - prev.base_altitude;
            temps[i] = temps[i - 1] + prev.lapse_rate * dh;
        }
        return temps;
}();

// L!=0 --->  P = Pb * (T / Tb) ^ (-g / R*Lb)
// L = 0 ---> P = Pb exp ( -g*(h-h_b) / R*Tb)
// numerical_value_in for pow in compile-time
inline constexpr  std::array<quantity<Pa>, atmo_layers.size()> layer_base_press = []{
    std::array<quantity<Pa>, atmo_layers.size()> press{};
        press[0] = Sea_level_pressure;
        for (size_t i = 1; i < atmo_layers.size(); ++i) {
            const auto& prev = atmo_layers[i - 1];
        
            if (prev.lapse_rate != delta<K/m>(0)){  
                const double exponent =(-Standard_gravity / (Dry_air_specific_gas_constant * prev.lapse_rate))
                .numerical_value_in(mp_units::one);
                const double temp_ratio =(layer_base_temp[i] / layer_base_temp[i - 1])
                .numerical_value_in(mp_units::one); 

                press[i] = press[i - 1] * std::pow(temp_ratio, exponent);
                    
            }
            else {                                 
                const auto allt = atmo_layers[i].base_altitude - prev.base_altitude;
                const auto exponent = - (Standard_gravity * allt / (Dry_air_specific_gas_constant*layer_base_temp[i-1]));

                press[i] = press[i - 1] * mp_units::exp(exponent);
            }
        }
        return press;
}();


inline const size_t Atmo_layer_isa::find_layer (quantity<m> geopot_al){
    size_t res = 0;
    for (size_t i = 0; i < atmo_layers.size(); ++i) {
        if (i + 1 == atmo_layers.size() || geopot_al < atmo_layers[i + 1].base_altitude) {
            res = i;
            break;
        }
    }
    return res;
}

// Tb + L(H-Hb)
inline const quantity<K> Atmo_layer_isa::compute_temperature(const size_t layer, const quantity<m> geopot_al) { 

    const auto dh = geopot_al - atmo_layers[layer].base_altitude;  // (H-Hb)
    return layer_base_temp[layer] + atmo_layers[layer].lapse_rate * dh; 
}

// L!=0 --->  P = Pb * (T / Tb) ^ (-g / R*Lb)
// L = 0 ---> P = Pb exp ( -g*(h-h_b) / R*Tb)
inline const quantity<Pa> Atmo_layer_isa::compute_pressure(const size_t layer,quantity<K>& temperature, const quantity<m> geopot_al, const quantity<kg/mol> molar_mass){
   
    if (atmo_layers[layer].lapse_rate != delta<K/m>(0)){ 

        double exponent =((-Standard_gravity * molar_mass) / (Gaz_constant * atmo_layers[layer].lapse_rate))
        .numerical_value_in(mp_units::one);
        double temp_ratio =(temperature / layer_base_temp[layer])
        .numerical_value_in(mp_units::one);

        return layer_base_press[layer] * std::pow(temp_ratio, exponent);
    } 
  
        const auto allt = geopot_al - atmo_layers[layer].base_altitude;
        const auto exponent = - (Standard_gravity * allt * molar_mass / (Gaz_constant*layer_base_temp[layer]));

        return layer_base_press[layer] * mp_units::exp(exponent);
    
}
inline void Atmo_layer_isa::print_layer_temp_press (){
    for (size_t i = 0; i<layer_base_temp.size(); ++i)
    {
        std::cout<< atmo_layers[i].base_altitude << layer_base_temp[i] << '\t' << layer_base_press[i] << '\n';
    }
}

