#pragma once
#include "../Constants.h"

struct Atmo_layer_termosphere
{

    //very rough calculation . F10.7 quantities was chosen roughly too. 
    //T_c = 383 + 3.32\,\bar F_{10.7} + 1.8\,(F_{10.7}-\bar F_{10.7}),(Jacchia-70/71, CIRA) 
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

