#pragma once
#include "../Constants.h"
#include <array>


struct Atmo_layer_isa {

    inline const size_t find_layer (quantity<m> geopot_al);  
    inline const quantity<K> compute_temperature (const size_t layer,quantity<m> geopot_al);
    inline const quantity<Pa> compute_pressure(const size_t layer,quantity<K>& temperature);
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

inline constexpr  std::array<quantity<K>, atmo_layers.size()> layer_base_temp = []{
    std::array<quantity<K>, atmo_layers.size()> temps{};
        temps[0] = sea_level_temperature;
        for (size_t i = 1; i < atmo_layers.size(); ++i) {
            const auto& prev = atmo_layers[i - 1];
            const auto dh = atmo_layers[i].base_altitude - prev.base_altitude;
            temps[i] = temps[i - 1] + prev.lapse_rate * dh;
        }
        return temps;
}();

inline constexpr  std::array<quantity<Pa>, atmo_layers.size()> layer_base_press = []{
    std::array<quantity<Pa>, atmo_layers.size()> press{};
        press[0] = sea_level_pressure;
        for (size_t i = 1; i < atmo_layers.size(); ++i) {
            const auto& prev = atmo_layers[i - 1];
        
            if (prev.lapse_rate != delta<K/m>(0)){  // P = Pb * (T / Tb) ^ (-g / R*Lb)
                const double exponent =(-standard_gravity / (dry_air_specific_gas_constant * prev.lapse_rate))
                .numerical_value_in(mp_units::one);
                const double temp_ratio =(layer_base_temp[i] / layer_base_temp[i - 1])
                .numerical_value_in(mp_units::one); // numerical_value_in for pow in compile-time

                press[i] = press[i - 1] * std::pow(temp_ratio, exponent);
                    
            }
            else {                                 // P = Pb exp ( -g*(h-h_b) / R*Tb)
                const auto allt = atmo_layers[i].base_altitude - prev.base_altitude;
                const auto exponent = - (standard_gravity * allt / (dry_air_specific_gas_constant*layer_base_temp[i-1]));

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
inline const quantity<K> Atmo_layer_isa::compute_temperature(const size_t layer,quantity<m> geopot_al) { 

    const auto dh = geopot_al - atmo_layers[layer].base_altitude;  // (H-Hb)
    return layer_base_temp[layer] + atmo_layers[layer].lapse_rate * dh; 
}

inline const quantity<Pa> Atmo_layer_isa::compute_pressure(const size_t layer,quantity<K>& temperature){
    if (layer == 0)
    {
        double exponent =(-standard_gravity / (dry_air_specific_gas_constant * atmo_layers[0].lapse_rate))
        .numerical_value_in(mp_units::one);;
        double temp_ratio =(temperature / layer_base_temp[0])
        .numerical_value_in(mp_units::one);

        return layer_base_press[0] * std::pow(temp_ratio, exponent);
    }
    const auto& prev = atmo_layers[layer - 1];
    if (prev.lapse_rate != delta<K/m>(0)){ 
        double exponent =(-standard_gravity / (dry_air_specific_gas_constant * prev.lapse_rate))
        .numerical_value_in(mp_units::one);;
        double temp_ratio =(temperature / layer_base_temp[layer - 1])
        .numerical_value_in(mp_units::one);

        return layer_base_press[layer-1] * std::pow(temp_ratio, exponent);
    } 
    else std::cout << "dfdd";
}
inline void Atmo_layer_isa::print_layer_temp_press (){
    for (size_t i = 0; i<layer_base_temp.size(); ++i)
    {
        std::cout<< atmo_layers[i].base_altitude << layer_base_temp[i] << '\t' << layer_base_press[i] << '\n';
    }
}

