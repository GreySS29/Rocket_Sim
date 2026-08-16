#pragma once
#include "../Constants.h"
#include <array>


struct Atmo_layer_isa {
    quantity<m> base_altitude;
    quantity<K/m> lapse_rate;  
    inline const quantity<K> compute_temperature (quantity<m> geopot_al);
};

inline constexpr auto sea_level_temperature  = delta<K>(288.15);
inline constexpr std::array<Atmo_layer_isa, 8> atmo_layers = {{
    {     0 * m, delta<K/m>(-0.0065)  },  // troposphere
    { 11'000 * m, delta<K/m>( 0.0)    },  // tropopause
    { 20'000 * m, delta<K/m>( 0.001)  },  // lower_stratosphere
    { 32'000 * m, delta<K/m>( 0.0028) },  // stratosphere
    { 47'000 * m, delta<K/m>( 0.0)    },  // stratopause
    { 51'000 * m, delta<K/m>(-0.0028) },  // mesosphere
    { 71'000 * m, delta<K/m>(-0.002)  },  // upper_mesosphere
    { 84'852 * m, delta<K/m>(-0.002)} , // 

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


inline const quantity<K> Atmo_layer_isa::compute_temperature(quantity<m> geopot_al) { 
    size_t res = 0;
    for (size_t i = 0; i < atmo_layers.size(); ++i) {
        if (i + 1 == atmo_layers.size() || geopot_al < atmo_layers[i + 1].base_altitude) {
            res = i;
            break;
        }
    }
    const auto dh = geopot_al - atmo_layers[res].base_altitude;  // (H-Hb)
    return layer_base_temp[res] + atmo_layers[res].lapse_rate * dh; 
}